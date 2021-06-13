#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/MainScene.hpp"
#include "ChessClock/Game.hpp"
#include "ChessClock/MainScene.Values.hpp"

namespace ChessClock
{
    using namespace Gambit;

    bool MainScene::Setup(Context& ctx)
    {
        ctx.values = std::make_shared<Values>();
        Renderer& renderer = ctx.renderer;
        ResourceManager& resources = ctx.resources;
        auto& values = *ctx.values;

        values.font = resources.LoadResource<Font>("AdobeFanHeitiStd-Bold.otf", 125);
        values.headerFont = resources.LoadResource<Font>("AdobeFanHeitiStd-Bold.otf", 30);
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,255 });

        values.leftNameText = values.headerFont->CreateTexture(resources, renderer, "Spamfilter", { 255,5,0 });
        values.rightNameText = values.headerFont->CreateTexture(resources, renderer, "monoRAIL", { 255,255,255 });
        values.versusText = values.headerFont->CreateTexture(resources, renderer, "vs", { 255,255,255 });

        values.atlas = resources.LoadResource<Atlas>("Lichess\\atlas", resources, &renderer);
        values.scene = resources.LoadResource<Scene>("Lichess\\scene_playing.json", resources, values.atlas);

        AddStep(ctx, &MainScene::RenderScene);
        AddStep(ctx, &MainScene::StepGame);
        AddStep(ctx, &MainScene::Present);

        values.game.SetGameState(EGameState::Playing);
        values.game.SetColor(ESide::Left, EColor::White);
        values.game.SetTimeControl(TimeControl{5, 0, 3});
        values.game.Pause();

        return true;
    }

    void MainScene::AddStep(Context& ctx, bool(MainScene::* method)(Context&))
    {
        ctx.steps.push_back([this, method](auto& ctx) { return (this->*method)(ctx); });
    }

    bool MainScene::RenderScene(Context& ctx)
    {
        auto& renderer = ctx.renderer;
        auto& values = *ctx.values;

        values.atlas->WriteSprite(renderer, "background", Rect{ 0,0,800,480 });
        values.scene->Render(ctx.renderer);

        int y = 14;
        renderer.WriteTexture(values.leftNameText, Vector2(85, y));
        renderer.WriteTexture(values.versusText, Vector2(400 - 12, y));
        renderer.WriteTexture(values.rightNameText, Vector2(580, y));

        values.debugTick = false;
        return true;
    }

    void DrawTimer(MainScene::Values& values, Renderer &renderer, Vector2 location, Player const& player)
    {
        values.numberFont->DrawTime(renderer, location,
            (uint8_t)player.GetMinutes(), (uint8_t)player.GetSeconds());
    }

    bool MainScene::StepGame(Context &ctx)
    {
        auto &values = *ctx.values;
        auto &renderer = ctx.renderer;
        auto &game = values.game;

        if (!game.IsPaused())
            game.Update();

        Vector2 destPointLeft{ 35, 95 };
        Vector2 destPointRight{ 438, 95 };

        DrawTimer(values, renderer, destPointLeft, game.LeftPlayer());
        DrawTimer(values, renderer, destPointRight, game.RightPlayer());

        return true;
    }

    bool MainScene::Present(Context &ctx)
    {
        return ctx.renderer.Present();
    }
}

