#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/Root.hpp"

#include <memory>

#include "ChessClock/EGameState.hpp"
#include "ChessClock/GameSplash.hpp"
#include "ChessClock/GamePlaying.hpp"
#include "ChessClock/GameSettings.hpp"
#include "ChessClock/GameAbout.hpp"

namespace ChessClock
{
    using namespace Gambit;

    int _fpsFrameCounter;
    float _lastTime;

    int Root::_frameNumber{ 0 };

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

    bool Root::Setup(Context& context)
    {
        context.values = std::make_shared<Values>();
        LoadResources(context);

        AddStep(context, &Root::RenderScene);
        AddStep(context, &Root::StepGame);
        AddStep(context, &Root::Present);

        Prepare(context);

        return true;
    }

    ScenePtr LoadScene(string const &themeName, string const &name, ResourceManager& resources, AtlasPtr const &atlas)
    {
        return resources.LoadResource<Scene>((themeName + "/scenes/" + name + ".json").c_str(), &resources, atlas);
    }

    void Root::LoadResources(Context &context)
    {
        auto &values = *context.values;
        auto &resources = context.resources;
        auto &renderer = context.renderer;
        
        values.font = resources.LoadResource<Font>(_defaultFont.c_str(), 125);
        values.atlas = resources.LoadResource<Atlas>((_themeName + "/atlas").c_str(), &resources, &renderer);

        values.headerFont = resources.LoadResource<Font>(_defaultFont.c_str(), 30);
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,255 });

        values.leftNameText = values.headerFont->CreateTexture(resources, renderer, "SpamFilter", { 255,255,255 });
        values.rightNameText = values.headerFont->CreateTexture(resources, renderer, "monoRAIL", { 255,255,255 });
        values.versusText = values.headerFont->CreateTexture(resources, renderer, "vs", { 255,255,255 });

        auto load = [&](const char *name) { return resources.LoadResource<Scene>((_themeName + "/scenes/" + name + ".json").c_str(), &resources, values.atlas); };
        auto sceneSplash = load("splash");
        auto scenePlaying = load("playing");
        auto sceneSettings = load("settings");
        auto sceneAbout = load("about");

        auto gameSplash = std::make_shared<GameSplash>();
        auto gamePlaying = std::make_shared<GamePlaying>();
        auto gameSettings = std::make_shared<GameSettings>();
        auto gameAbout = std::make_shared<GameAbout>();

        values.pages[EPage::Splash] = std::make_shared<Page<GameSplash>>(gameSplash, sceneSplash);
        values.pages[EPage::Playing] = std::make_shared<Page<GamePlaying>>(gamePlaying, scenePlaying);
        values.pages[EPage::Settings] = std::make_shared<Page<GameSettings>>(gameSettings, sceneSettings);
        values.pages[EPage::About] = std::make_shared<Page<GameAbout>>(gameAbout, sceneAbout);

        for (auto & [first, second] : values.pages)
        {
            second->GameBase->Prepare(context);
        }

        //CJS TODO
        values.pageCurrent = EPage::Splash;
        //values.sceneCurrent = values.scenePlaying;

        //values.game = values.gameSplash;

        //Transition(values.gameSplash);
    }

    void Root::Prepare(Context &ctx)
    {
        Values &values = *ctx.values;
        auto game = values.GetCurrentGame();
        if (!game)
        {
            LOG_ERROR() << "No start game object given.\n";
            return;
        }

        game->Prepare(ctx);
    }

    void Root::AddStep(Context& ctx, bool(Root::*method)(Context&))
    {
        ctx.steps.push_back([this, method](auto &context) { return (this->*method)(context); });
    }

    bool Root::RenderScene(Context& ctx)
    {
        ctx.values->GetCurrentGame()->Render(ctx);
        ctx.values->debugTick = false;

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

        auto &values = *context.values;
        values.GetCurrentGame()->Update(context);

        return true;
    }

    bool Root::Present(Context &ctx)
    {
        return ctx.renderer.Present();
    }

    void Root::OnPressed(Context &ctx, const Vector2 &where)
    {
        const auto scene = ctx.values->GetCurrentScene();
        const auto &button = scene->OnPressed(ctx.values->atlas, where);
        if (!button)
            return;

        ctx.values->GetCurrentGame()->Call(ctx, button);
    }

    void Root::Transition(Context &context, EPage next)
    {
        if (context.values->GetCurrentGame())
        {
            //CJS TODO: leave current page
        }

        LOG_INFO() << "Transitioning to " << next << "\n";

        context.values->pageCurrent = next;
    }

}

