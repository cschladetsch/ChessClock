#include "Gambit/Font.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/NumberFont.hpp"

#include "ChessClock/MainScene.hpp"
#include "ChessClock/Game.hpp"

namespace ChessClock
{
    using namespace Gambit;

    struct MainScene::Values
    {
        FontPtr font;
        TexturePtr background;
        TexturePtr text;
        NumberFontPtr numberFont;
        Rect bounds;

        Game game;
    };

    bool MainScene::Setup(Ctx &ctx)
    {
        ctx.values = std::make_shared<Values>();
        Renderer &renderer = ctx.renderer;
        ResourceManager &resources = ctx.resources;
        auto& values = *ctx.values;

        values.font = resources.LoadResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
        values.background = resources.LoadResource<Texture>("sample.bmp", &renderer, 800, 480);
        values.numberFont = resources.CreateResource<NumberFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,0 });
        values.text = values.font->CreateTexture(resources, renderer, "Hello world", { 255,255,255 });
        values.bounds = values.text->GetBounds();

        ctx.steps.push_back([this](auto& ctx) { return MainScene::StepWriteBackground(ctx); });
        ctx.steps.push_back([this](auto& ctx) { return MainScene::StepWriteText(ctx); });
        ctx.steps.push_back([this](auto& ctx) { return MainScene::StepWriteTimers(ctx); });
        ctx.steps.push_back([this](auto& ctx) { return MainScene::StepPresent(ctx); });

        return true;
    }

    bool MainScene::Step(Ctx &ctx)
    {
        //return ctx.renderer.Clear();
        return true;
    }

    bool MainScene::StepWriteBackground(Ctx &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->background, nullptr, nullptr);
    }

    bool MainScene::StepWriteText(Ctx &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->text, nullptr, &ctx.values->bounds);
    }

    bool MainScene::StepWriteTimers(Ctx &ctx)
    {
        Vector2 destPoint{ 100, 100 };
        uint32_t millis = SDL_GetTicks();
        uint32_t seconds = millis / 1000;
        uint32_t minutes = seconds / 60;
        ctx.values->numberFont->DrawTime(ctx.renderer, destPoint, minutes%60, seconds%60, millis%100);
        return true;
    }

    bool MainScene::StepPresent(Ctx &ctx)
    {
        return ctx.renderer.Present();
    }

    bool MainScene::ProcessEvents(Ctx &ctx)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                exit(0);
                break;
            }
        }

        return true;
    }
}
