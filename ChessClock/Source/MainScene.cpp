#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/MainScene.hpp"
#include "ChessClock/Game.hpp"
#include "ChessClock/Global.hpp"
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

        values.font = resources.LoadResource<Font>("AdobeFanHeitiStd-Bold.otf", 120);
        values.background = resources.LoadResource<Texture>("sample.bmp", &renderer, global.ScreenWidth(), global.ScreenHeight());
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,0 });
        values.text = values.font->CreateTexture(resources, renderer, "Hello world", { 255,255,255 });
        values.textBounds = values.text->GetBounds();
        values.atlas = resources.LoadResource<Atlas>("Lichess\\atlas", resources, &renderer);

        AddStep(ctx, &MainScene::StepWriteBackground);
        //AddStep(ctx, &MainScene::StepWriteText);
        AddStep(ctx, &MainScene::StepWriteTimers);
        AddStep(ctx, &MainScene::StepPresent);

        return true;
    }

    void MainScene::AddStep(Context& ctx, bool(MainScene::* method)(Context&))
    {
        ctx.steps.push_back([this, method](auto& ctx) { return (this->*method)(ctx); });
    }

    bool MainScene::StepWriteBackground(Context &ctx)
    {
        auto& atlas = ctx.values->atlas;
        auto& renderer = ctx.renderer;

        atlas->WriteSprite(renderer, "background", Rect{ 0,0,800,480 });
        WriteHeader(*atlas, ctx.values->font, renderer);
        WriteButtons(*atlas, renderer);
        WriteFooter(*atlas, ctx.values->font, renderer);

        return true;

    }

    void MainScene::WriteHeader(Atlas const& atlas, FontPtr, Renderer& renderer) const
    {
    }

    void MainScene::WriteFooter(Atlas const& atlas, FontPtr, Renderer& renderer) const
    {
    }

    void MainScene::WriteButtons(Atlas const &atlas, Renderer &renderer) const
    {
        atlas.WriteSprite(renderer, "icon_settings", Vector2{ 85, 295 });
        atlas.WriteSprite(renderer, "icon_pause", Vector2{ 350, 295 });
        atlas.WriteSprite(renderer, "icon_sound", Vector2{ 615, 295 });
    }

    bool MainScene::StepWriteText(Context &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->text, nullptr, &ctx.values->textBounds);
    }

    bool MainScene::StepWriteTimers(Context &ctx)
    {
        auto& values = ctx.values;
        auto& game = values->game;
        if (game.IsPaused())
        {
            return true;
        }
        uint32_t millis = SDL_GetTicks();
        auto &player = ctx.values->game.CurrentPlayer();
        player.UpdateTime(millis);
        Vector2 destPoint{ 75, 110 };
        uint32_t seconds = millis / 1000;
        uint32_t minutes = seconds / 60;
        ctx.values->numberFont->DrawTime(ctx.renderer, destPoint, minutes % 60, seconds % 60);
        return true;
    }

    bool MainScene::StepPresent(Context &ctx)
    {
        return ctx.renderer.Present();
    }

}

