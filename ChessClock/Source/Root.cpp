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

    void Root::MakeScreenOverlay(Context& context)
    {
        _fullscreenBlack = SDL_CreateTexture(context.Renderer.GetRenderer(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, global.GetScreenWidth(), global.GetScreenHeight());
    }

    bool Root::Setup(Context& context)
    {
        MakeScreenOverlay(context);
        
        context.Values = make_shared<Values>();
        LoadResources(context);

        AddStep(context, &Root::RenderScene);
        AddStep(context, &Root::StepGame);
        AddStep(context, &Root::Present);

        Prepare(context);

        return true;
    }

    ScenePtr LoadScene(string const &themeName, string const &name, ResourceManager& resources, AtlasPtr const &atlas)
    {
        return resources.LoadResource<Scene>(themeName + "/scenes/" + name + ".json", &resources, atlas);
    }

    template <class PageType, class Loader>
    SharedPtr<PageBase> LoadPage(const char *name, Loader loader)
    {
        return make_shared<Page<PageType>>(make_shared<PageType>(), loader(name));
    }

    void Root::LoadResources(Context &context)
    {
        auto &values = *context.Values;
        auto &resources = context.Resources;
        auto &renderer = context.Renderer;
        const auto white = Color{ 255,255,255 };

        values.Root = this;
        values.Theme = resources.LoadResource<ThemeMeta>(_themeName + "/meta.json", &resources);

        values.TimerFont = values.Theme->GetFont("timer_font");
        values.SmallFont = values.Theme->GetFont("small_font");
        values.HeaderFont = values.Theme->GetFont("small_font");

        values.Atlas = resources.LoadResource<Atlas>(_themeName + "/Atlas", &resources, &renderer);

        values.NumberFont = resources.CreateResource<TimerFont>("Numbers", values.TimerFont);
        values.NumberFont->MakeTextures(resources, renderer, white);

        auto makeText = [&](const char *text, const Color color) {
            return values.HeaderFont->CreateText(resources, renderer, text, color);
        };
        values.LeftNameText = makeText("SpamFilter", white);
        values.RightNameText = makeText("monoRAIL", white);
        values.VersusText = makeText("vs", white);

        auto loadPage = [&](const char *name) {
            return resources.LoadResource<Scene>(_themeName + "/scenes/" + name + ".json", &resources, values.Atlas);
        };
        values.Pages[EPage::Splash] = LoadPage<GameSplash>("splash", loadPage);
        values.Pages[EPage::Playing] = LoadPage<GamePlaying>("playing", loadPage);
        values.Pages[EPage::Settings] = LoadPage<GameSettings>("settings", loadPage);
        values.Pages[EPage::About] = LoadPage<GameAbout>("about", loadPage);

        for (auto & [first, second] : values.Pages)
            second->GameBase->Prepare(context);

        Transition(context, EPage::Splash);
    }

    void Root::Prepare(Context &ctx)
    {
    }

    void Root::AddStep(Context& ctx, bool(Root::*method)(Context&))
    {
        ctx.Steps.push_back([this, method](auto &context) { return (this->*method)(context); });
    }

    bool Root::RenderScene(Context& context)
    {
        context.Values->GetCurrentGame()->Render(context);

        //CJS TODO transitions
        //if (_transitionTime > 0 && Gambit::TimeNowMillis() < _transitionTime)
        //{
        //    auto delta = _transitionTime - _transitionStartTime;
        //    auto normalised = static_cast<float>(delta) / _transitionTotalTime;
        //    auto alpha = normalised < 0.5f ? normalised : 1 - normalised;
        //    auto Renderer = context.Renderer.GetRenderer();

        //    int result = 0;
        //    //CJS TODO: fade to black then into new scene
        //    //LOG_DEBUG() << LOG_VALUE(alpha) << "\n";
        //    //CALL_SDL(SDL_SetTextureAlphaMod(_fullscreenBlack, alpha * 255));
        //    uint8_t texAlpha{ 0 };
        //    CALL_SDL(SDL_SetTextureBlendMode(_fullscreenBlack, SDL_BLENDMODE_BLEND));
        //    CALL_SDL(SDL_GetTextureAlphaMod(_fullscreenBlack, &texAlpha));
        //    CALL_SDL(SDL_SetTextureAlphaMod(_fullscreenBlack, 128));
        //    CALL_SDL(SDL_RenderCopy(Renderer, _fullscreenBlack, nullptr, nullptr));
        //}

        context.Values->DebugTick = false;

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

        auto &values = *context.Values;
        values.GetCurrentGame()->Update(context);

        return true;
    }

    bool Root::Present(Context &ctx)
    {
        return ctx.Renderer.Present();
    }

    void Root::OnPressed(Context &ctx, const Vector2 &where)
    {
        const auto scene = ctx.Values->GetCurrentScene();
        const auto &button = scene->OnPressed(ctx.Values->Atlas, where);
        if (!button)
            return;

        ctx.Values->GetCurrentGame()->Call(ctx, button);
    }

    void Root::Transition(Context &context, EPage next)
    {
        //if (context.Values->GetCurrentGame())
        //{
        //    //CJS TODO: leave current page
        //}

        //CJS TODO: transitions
        //auto now = Gambit::TimeNowMillis();
        //_transitionStartTime = now;
        //_transitionTime = now + _transitionTotalTime;
        //_transitionPage = next;

        LOG_INFO() << "Transitioning to " << LOG_VALUE(next) << "\n";

        context.Values->PageCurrent = next;
    }

    void Root::UpdateTransition(Context &context)
    {
        auto now = Gambit::TimeNowMillis();
        //LOG_DEBUG() << LOG_VALUE(now) << LOG_VALUE(_transitionTime) << "\n";
        if (now > _transitionTime)
        {
            context.Values->PageCurrent = _transitionPage;
            _transitionTime = 0;
        }
    }
}

