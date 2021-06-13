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

        values.leftNameText = values.headerFont->CreateTexture(resources, renderer, "Spamfilter", { 255,255,255 });
        values.rightNameText = values.headerFont->CreateTexture(resources, renderer, "monoRAIL", { 255,255,255 });
        values.versusText = values.headerFont->CreateTexture(resources, renderer, "vs", { 255,255,255 });

        values.atlas = resources.LoadResource<Atlas>("Lichess\\atlas", resources, &renderer);
        values.scene = resources.LoadResource<Scene>("Lichess\\scene_playing.json", resources);

        AddStep(ctx, &MainScene::StepWriteBackground);
        AddStep(ctx, &MainScene::StepGame);
        AddStep(ctx, &MainScene::StepPresent);

        values.game.SetGameState(EGameState::Playing);
        values.game.SetColor(ESide::Left, EColor::White);
        values.game.SetTimeControl(TimeControl{5, 0, 5});
        values.game.Pause();

        return true;
    }

    void MainScene::AddStep(Context& ctx, bool(MainScene::* method)(Context&))
    {
        ctx.steps.push_back([this, method](auto& ctx) { return (this->*method)(ctx); });
    }

    bool MainScene::StepWriteBackground(Context &ctx)
    {
        auto& atlas = *ctx.values->atlas;
        auto& renderer = ctx.renderer;
        auto& resources = ctx.resources;

        atlas.WriteSprite(renderer, "background", Rect{ 0,0,800,480 });
        auto left = atlas.GetSprite("left_side");
        atlas.WriteSprite(renderer, "left_side", left.second.GetTopLeft());

        WriteHeader(atlas, ctx, renderer);
        WriteButtons(atlas, renderer);
        WriteFooter(atlas, ctx, renderer);

        return true;
    }

    void MainScene::WriteHeader(Atlas const& atlas, Context &ctx, Renderer& renderer) const
    {
        Values const& values = *ctx.values;

        int y = 6;
        atlas.WriteSprite(renderer, "pawn_white", Vector2{ 30, y });
        atlas.WriteSprite(renderer, "pawn_black", Vector2{ 800 - 30 - 25, y });

        y = 14;
        renderer.WriteTexture(values.leftNameText, Vector2(85, y));
        renderer.WriteTexture(values.versusText, Vector2(400 - 12, y));
        renderer.WriteTexture(values.rightNameText, Vector2(580, y));
    }

    void MainScene::WriteFooter(Atlas const& atlas, Context &ctx, Renderer& renderer) const
    {
    }

    void MainScene::WriteButtons(Atlas const &atlas, Renderer &renderer) const
    {
        atlas.WriteSprite(renderer, "icon_settings", Vector2{ 85, 295 });
        atlas.WriteSprite(renderer, "icon_pause", Vector2{ 375, 295 });
        atlas.WriteSprite(renderer, "icon_sound", Vector2{ 615, 295 });
    }

    void DrawTimer(MainScene::Values& values, Renderer &renderer, Vector2 location, Player const& player)
    {
        values.numberFont->DrawTime(renderer, location,
            (uint8_t)player.GetMinutes(), (uint8_t)player.GetSeconds());
    }

    bool MainScene::StepGame(Context &ctx)
    {
        auto &values = *ctx.values;
        auto &game = values.game;
        auto &renderer = ctx.renderer;
        if (!game.IsPaused())
            game.Update();

        Vector2 destPointLeft{ 35, 95 };
        Vector2 destPointRight{ 438, 95 };
        auto const &left = game.LeftPlayer();
        auto const& right = game.RightPlayer();
        DrawTimer(values, renderer, destPointLeft, left);
        DrawTimer(values, renderer, destPointRight, right);

        return true;
    }

    bool MainScene::StepPresent(Context &ctx)
    {
        return ctx.renderer.Present();
    }
}

