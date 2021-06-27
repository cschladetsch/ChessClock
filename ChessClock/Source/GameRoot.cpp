#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/ForwardReferences.hpp"

#include "ChessClock/Global.hpp"
#include "ChessClock/Values.hpp"

#include "ChessClock/GameRoot.hpp"
#include "ChessClock/GamePlaying.hpp"

namespace ChessClock
{
    using namespace Gambit;

    int _frames;
    float _lastTime;
    int GameRoot::_frameNumber{ 0 };

    bool GameRoot::ParseJson(JsonNext &item)
    {
        auto &key = item.key();

        auto found = _jsonToMember.find(key);
        if (found == _jsonToMember.end())
        {
            LOG_WARN() << "No member named '" << key << "' found in MainScene\n";
            return false;
        }

        (this->*found->second) = item.value();

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

    void GameRoot::Prepare(Context &ctx)
    {
        Values &values = *ctx.values;
        values.playing->SetGameState(EGameState::Playing);
        values.playing->SetColor(ESide::Left, EColor::White);
        values.playing->SetTimeControl(TimeControl{5, 0, 3});
        values.playing->Pause();

        values.playing->AddCallback("SettingsPressed", [this, &ctx](auto &ctx, auto source) { SettingsPressed(ctx, source); });
        values.playing->AddCallback("PausePressed", [this, &ctx](auto &ctx, auto source) { PausePressed(ctx, source); });
        values.playing->AddCallback("VolumePressed", [this, &ctx](auto &ctx, auto source) { VolumePressed(ctx, source); });
    }

    void GameRoot::SettingsPressed(Context &context, ObjectPtr sourceObject)
    {
        LOG_DEBUG() << "Settings pressed from " << LOG_VALUE(sourceObject->GetName()) << "\n";
    }

    void GameRoot::PausePressed(Context &context, ObjectPtr sourceObject)
    {
        LOG_DEBUG() << "Pause pressed from " << LOG_VALUE(sourceObject->GetName()) << "\n";
        //context.values->game.TogglePause();
    }

    void GameRoot::VolumePressed(Context &context, ObjectPtr sourceObject)
    {
        LOG_DEBUG() << "Volume pressed from " << LOG_VALUE(sourceObject->GetName()) << "\n";
    }

    void GameRoot::LoadResources(ResourceManager &resources, Renderer &renderer, Values &values)
    {
        values.font = resources.LoadResource<Font>(_defaultFont.c_str(), 125);
        values.headerFont = resources.LoadResource<Font>(_defaultFont.c_str(), 30);
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,255 });
        values.leftNameText = values.headerFont->CreateTexture(resources, renderer, "Spamfilter", { 255,255,255 });
        values.rightNameText = values.headerFont->CreateTexture(resources, renderer, "monoRAIL", { 255,255,255 });
        values.versusText = values.headerFont->CreateTexture(resources, renderer, "vs", { 255,255,255 });
        values.atlas = resources.LoadResource<Atlas>((_themeName + "/atlas").c_str(), &resources, &renderer);

        //values.sceneSplash = resources.LoadResource<Scene>((_themeName + "/scenes/splash.json").c_str(), &resources, values.atlas);
        values.scenePlaying = resources.LoadResource<Scene>((_themeName + "/scenes/playing.json").c_str(), &resources, values.atlas);
        //values.sceneSettings = resources.LoadResource<Scene>((_themeName + "/scenes/settings.json").c_str(), &resources, values.atlas);
        //values.sceneAbout = resources.LoadResource<Scene>((_themeName + "/scenes/about.json").c_str(), &resources, values.atlas);

        //values.sceneCurrent = values.sceneSplash;
        values.sceneCurrent = values.scenePlaying;

        values.playing = std::make_shared<GamePlaying>();

        SetupGameSprites(resources, renderer, values);
    }

    void GameRoot::SetupGameSprites(ResourceManager &, Renderer &, Values &values)
    {
        auto &scene = *values.scenePlaying;
        auto leftFace = scene.FindChild("left_clock_face");
        auto rightFace = scene.FindChild("right_clock_face");
        auto whitePawn = scene.FindChild("pawn_white");
        auto blackPawn = scene.FindChild("pawn_black");
        auto pauseButton = scene.FindChild("icon_pause");
        values.playing->SetSprites(leftFace, rightFace, whitePawn, blackPawn, pauseButton);
    }

    void GameRoot::AddStep(Context& ctx, bool(GameRoot::* method)(Context&))
    {
        ctx.steps.push_back([this, method](auto& ctx) { return (this->*method)(ctx); });
    }

    bool GameRoot::RenderScene(Context& ctx)
    {
        ctx.values->playing->Render(ctx);

        ctx.values->debugTick = false;
        return true;
    }

    void GameRoot::DebugFrameRate()
    {
        ++_frames;
        auto now = TimeNowSeconds();
        auto deltaSeconds = now - _lastTime;
        if (deltaSeconds > 5)
        {
            _lastTime = now;
            auto fps = round((_frames) / deltaSeconds);
            LOG_DEBUG() << LOG_VALUE(fps) << "\n";
            _frames = 0;
        }
    }

    bool GameRoot::StepGame(Context &ctx)
    {
        if (_showFps == "true")
            DebugFrameRate();

        ++_frameNumber;

        auto &values = *ctx.values;
        auto &renderer = ctx.renderer;
        auto &game = values.game;

        values.playing->Update(ctx);

        return true;
    }

    bool GameRoot::Present(Context &ctx)
    {
        return ctx.renderer.Present();
    }

    void GameRoot::OnPressed(Context &ctx, Vector2 where)
    {
        auto &scene = ctx.values->sceneCurrent;
        ObjectPtr button = scene->OnPressed(ctx.values->atlas, where);
        if (!button)
            return;

        ctx.values->playing->Call(ctx, button);
    }
}

