#include "Gambit/Atlas.hpp"
#include "Gambit/TimerFont.hpp"

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/Root.hpp"
#include "ChessClock/EGameState.hpp"
#include "ChessClock/GameSplash.hpp"
#include "ChessClock/GamePlaying.hpp"
#include "ChessClock/GameSettings.hpp"
#include "ChessClock/GameAbout.hpp"
#include "ChessClock/Global.hpp"
#include "ChessClock/ThemeMeta.hpp"

namespace ChessClock
{
    using namespace std;
    using namespace Gambit;

    int _fpsFrameCounter;
    float _lastTime;

    int Root::_frameNumber{ 0 };

    Root::~Root()
    {
        SDL_DestroyTexture(_fullscreenBlack);
    }

    bool Root::ParseJson(JsonNext &item)
    {
        auto &key = item.key();

        const auto found = _jsonToMember.find(key);
        if (found == _jsonToMember.end())
        {
            LOG_WARN() << "No member named '" << key << "' found in MainScene\n";
            return false;
        }

        this->*found->second = item.value();

        return true;
    }

    void Root::MakeScreenOverlay(Context &context)
    {
        _fullscreenBlack = SDL_CreateTexture(context.TheRenderer.GetRenderer(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, global.GetScreenWidth(), global.GetScreenHeight());
    }

    bool Root::Setup(Context &context)
    {
        MakeScreenOverlay(context);
        LoadResources(context);

        AddStep(context, &Root::RenderScene);
        AddStep(context, &Root::StepGame);
        AddStep(context, &Root::Present);

        Prepare(context);

        return true;
    }

    void Root::LoadResources(Context &context)
    {
        context.MyValues = make_shared<Values>();
        LoadTheme(context);
        LoadText(context);
        LoadPages(context);
        CreateObjectTexts(context);
        Transition(context, EPage::Splash);
    }

    void Root::CreateObjectTexts(Context &context)
    {
        for (auto const &[id, object] : context.Resources.GetAllObjects())
        {
            if (object->ObjectType == EObjectType::Text)
            {
                auto const &font = context.MyValues->Theme->GetFont(object->FontName);
                if (!font)
                    continue;

                object->TextTexturePtr = font->CreateText(context.Resources, context.TheRenderer, object->String, Color{ 255,255,255 });
            }
        }
    }

    void Root::LoadTheme(Context &context)
    {
        auto &values = *context.MyValues;
        auto &resources = context.Resources;
        auto &renderer = context.TheRenderer;
        auto &theme = values.Theme;
        
        values.MyRoot = this;
        theme = resources.LoadResource<ThemeMeta>(_themeName + "/meta.json", &resources);
        values.TimerFont = theme->GetFont("timer_font");
        values.SmallFont = theme->GetFont("small_font");
        values.HeaderFont = theme->GetFont("small_font");
        values.Atlas = resources.LoadResource<Atlas>(_themeName + "/atlas", &resources, &renderer);
    }

    void Root::LoadText(Context &context)
    {
        auto &values = *context.MyValues;
        auto &resources = context.Resources;
        auto &renderer = context.TheRenderer;
        const auto white = Color{ 255,255,255 };

        values.NumberFont = resources.CreateResource<TimerFont>("Numbers", values.TimerFont);
        values.NumberFont->MakeTextures(resources, renderer, white);

        auto makeText = [&](const char *text, const Color color) {
            return values.HeaderFont->CreateText(resources, renderer, text, color);
        };

        values.LeftNameText = makeText("SpamFilter", white);
        values.RightNameText = makeText("monoRAIL", white);
        values.VersusText = makeText("vs", white);
    }

    template <class PageType, class Loader>
    SharedPtr<PageBase> LoadPage(const char *name, Loader loader)
    {
        return make_shared<Page<PageType>>(make_shared<PageType>(), loader(name));
    }

    void Root::LoadPages(Context &context)
    {
        auto &values = *context.MyValues;
        auto &resources = context.Resources;
        auto loadPage = [&](const char *name) {
            return resources.LoadResource<Scene>(_themeName + "/scenes/" + name + ".json", &resources, values.Atlas);
        };

        values.Pages[EPage::Splash] = LoadPage<GameSplash>("splash", loadPage);
        values.Pages[EPage::Playing] = LoadPage<GamePlaying>("playing", loadPage);
        values.Pages[EPage::Settings] = LoadPage<GameSettings>("settings", loadPage);
        values.Pages[EPage::About] = LoadPage<GameAbout>("about", loadPage);
    }

    void Root::Prepare(Context &context)
    {
        auto &values = *context.MyValues;
        for (auto &[first, second] : values.Pages)
            second->GameBase->Prepare(context);
    }

    void Root::AddStep(Context& ctx, bool(Root::*method)(Context&))
    {
        ctx.Steps.push_back([this, method](auto &context) { return (this->*method)(context); });
    }

    bool Root::RenderScene(Context& context)
    {
        context.MyValues->GetCurrentGame()->Render(context);

        //CJS TODO transitions
        //if (_transitionTime > 0 && Gambit::TimeNowMillis() < _transitionTime)
        //{
        //    auto delta = _transitionTime - _transitionStartTime;
        //    auto normalised = static_cast<float>(delta) / _transitionTotalTime;
        //    auto alpha = normalised < 0.5f ? normalised : 1 - normalised;
        //    auto TheRenderer = context.TheRenderer.GetRenderer();

        //    int result = 0;
        //    //CJS TODO: fade to black then into new scene
        //    //LOG_DEBUG() << LOG_VALUE(alpha) << "\n";
        //    //CALL_SDL(SDL_SetTextureAlphaMod(_fullscreenBlack, alpha * 255));
        //    uint8_t texAlpha{ 0 };
        //    CALL_SDL(SDL_SetTextureBlendMode(_fullscreenBlack, SDL_BLENDMODE_BLEND));
        //    CALL_SDL(SDL_GetTextureAlphaMod(_fullscreenBlack, &texAlpha));
        //    CALL_SDL(SDL_SetTextureAlphaMod(_fullscreenBlack, 128));
        //    CALL_SDL(SDL_RenderCopy(TheRenderer, _fullscreenBlack, nullptr, nullptr));
        //}

        context.MyValues->DebugTick = false;

        return true;
    }

    void Root::ShowFrameRate() const
    {
        ++_fpsFrameCounter;
        const auto now = TimeNowSeconds();
        if (const auto deltaSeconds = now - _lastTime; deltaSeconds > 5)
        {
            _lastTime = now;
            const auto fps = round(static_cast<float>(_fpsFrameCounter) / deltaSeconds);
            LOG_INFO() << LOG_VALUE(fps) << "\n";
            _fpsFrameCounter = 0;
        }
    }

    bool Root::StepGame(Context &context)
    {
        if (_showFps == "true")
            ShowFrameRate();

        ++_frameNumber;

        //CJS TODO transitions
        //if (_transitionTime > 0)
        //{
        //    UpdateTransition(context);
        //    return true;
        //}

        auto &values = *context.MyValues;
        values.GetCurrentGame()->Update(context);

        return true;
    }

    bool Root::Present(Context &ctx)
    {
        return ctx.TheRenderer.Present();
    }

    void Root::OnPressed(Context &ctx, const Vector2 &where)
    {
        const auto scene = ctx.MyValues->GetCurrentScene();
        const auto &button = scene->OnPressed(ctx.MyValues->Atlas, where);
        if (!button)
            return;

        ctx.MyValues->GetCurrentGame()->Call(ctx, button);
    }

    void Root::Transition(Context &context, EPage next)
    {
        //if (context.MyValues->GetCurrentGame())
        //{
        //    //CJS TODO: leave current page
        //}

        //CJS TODO: transitions
        //auto now = Gambit::TimeNowMillis();
        //_transitionStartTime = now;
        //_transitionTime = now + _transitionTotalTime;
        //_transitionPage = next;

        LOG_INFO() << "Transitioning to " << LOG_VALUE(next) << "\n";

        context.MyValues->PageCurrent = next;
    }

    void Root::UpdateTransition(Context &context)
    {
        auto now = Gambit::TimeNowMillis();
        //LOG_DEBUG() << LOG_VALUE(now) << LOG_VALUE(_transitionTime) << "\n";
        if (now > _transitionTime)
        {
            context.MyValues->PageCurrent = _transitionPage;
            _transitionTime = 0;
        }
    }
}

