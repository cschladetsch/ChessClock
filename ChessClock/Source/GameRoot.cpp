#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/GameRoot.hpp"

#include "ChessClock/EGameState.hpp"
#include "ChessClock/ESide.hpp"
#include "ChessClock/GameSplash.hpp"
#include "ChessClock/GamePlaying.hpp"

namespace ChessClock
{
    using namespace Gambit;

    int _fpsFrameCounter;
    float _lastTime;

    int GameRoot::_frameNumber{ 0 };

    bool GameRoot::ParseJson(JsonNext &item)
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

    bool GameRoot::Setup(Context& ctx)
    {
        ctx.values = std::make_shared<Values>();
        LoadResources(ctx.resources, ctx.renderer, *ctx.values);

        AddStep(ctx, &GameRoot::RenderScene);
        AddStep(ctx, &GameRoot::StepGame);
        AddStep(ctx, &GameRoot::Present);

        Prepare(ctx);

        return true;
    }

    ScenePtr LoadScene(string const &themeName, string const &name, ResourceManager& resources, AtlasPtr const &atlas)
    {
        return resources.LoadResource<Scene>((themeName + "/scenes/" + name + ".json").c_str(), &resources, atlas);
    }

    void GameRoot::LoadResources(ResourceManager &resources, Renderer &renderer, Values &values)
    {
        values.font = resources.LoadResource<Font>(_defaultFont.c_str(), 125);
        values.atlas = resources.LoadResource<Atlas>((_themeName + "/atlas").c_str(), &resources, &renderer);

        values.headerFont = resources.LoadResource<Font>(_defaultFont.c_str(), 30);
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,255 });

        values.leftNameText = values.headerFont->CreateTexture(resources, renderer, "SpamFilter", { 255,255,255 });
        values.rightNameText = values.headerFont->CreateTexture(resources, renderer, "monoRAIL", { 255,255,255 });
        values.versusText = values.headerFont->CreateTexture(resources, renderer, "vs", { 255,255,255 });

        values.sceneSplash = LoadScene(_themeName, "splash", resources, values.atlas);
        values.scenePlaying = LoadScene(_themeName, "playing", resources, values.atlas);
        values.sceneSettings = LoadScene(_themeName, "settings", resources, values.atlas);
        values.sceneAbout = LoadScene(_themeName, "about", resources, values.atlas);

        //CJS TODO
        values.sceneCurrent = values.sceneSplash;
        values.sceneCurrent = values.scenePlaying;

        values.gameSplash = std::make_shared<GameSplash>();
        values.gamePlaying = std::make_shared<GamePlaying>();

        values.game = values.gamePlaying;

        //Transition(values.gameSplash);
    }

    void GameRoot::Prepare(Context &ctx)
    {
        Values &values = *ctx.values;
        auto &game = values.game;
        if (!game)
        {
            LOG_ERROR() << "No start game object given.\n";
            return;
        }

        game->Prepare(ctx);
    }

    void GameRoot::AddStep(Context& ctx, bool(GameRoot::*method)(Context&))
    {
        ctx.steps.push_back([this, method](auto &context) { return (this->*method)(context); });
    }

    bool GameRoot::RenderScene(Context& ctx)
    {
        ctx.values->gamePlaying->Render(ctx);
        ctx.values->debugTick = false;

        return true;
    }

    void GameRoot::ShowFrameRate() const
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

    bool GameRoot::StepGame(Context &context)
    {
        if (_showFps == "true")
            ShowFrameRate();

        ++_frameNumber;

        auto &values = *context.values;
        values.game->Update(context);

        return true;
    }

    bool GameRoot::Present(Context &ctx)
    {
        return ctx.renderer.Present();
    }

    void GameRoot::OnPressed(Context &ctx, const Vector2 &where)
    {
        auto &scene = ctx.values->sceneCurrent;
        const auto &button = scene->OnPressed(ctx.values->atlas, where);
        if (!button)
            return;

        ctx.values->game->Call(ctx, button);
    }

    void GameRoot::Transition(Context &context, PageBasePtr next)
    {
        if (context.values->game)
        {
            
        }

        //context.values->page = next;
    }

}

