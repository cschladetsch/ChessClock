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
        Rect textBounds;
        NumberFontPtr numberFont;
        Game game;
    };

    bool MainScene::Setup(Ctx& ctx)
    {
        ctx.values = std::make_shared<Values>();
        Renderer& renderer = ctx.renderer;
        ResourceManager& resources = ctx.resources;
        auto& values = *ctx.values;

        values.font = resources.LoadResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
        values.background = resources.LoadResource<Texture>("sample.bmp", &renderer, 800, 480);
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,0 });
        values.text = values.font->CreateTexture(resources, renderer, "Hello world", { 255,255,255 });
        values.textBounds = values.text->GetBounds();

        AddStep(ctx, &MainScene::StepWriteBackground);
        AddStep(ctx, &MainScene::StepWriteText);
        AddStep(ctx, &MainScene::StepWriteTimers);
        AddStep(ctx, &MainScene::StepPresent);

        return true;
    }

    void MainScene::AddStep(Ctx& ctx, bool(MainScene::* method)(Ctx&))
    {
        ctx.steps.push_back([this, method](auto& ctx) { return (this->*method)(ctx); });
    }

    bool MainScene::StepWriteBackground(Ctx &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->background, nullptr, nullptr);
    }

    bool MainScene::StepWriteText(Ctx &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->text, nullptr, &ctx.values->textBounds);
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
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        {
                            exit(0);
                            return false;
                        }

                        case SDLK_LEFT:
                        {
                            LOG_INFO() << "Pressed left\n";
                            break;
                        }

                        case SDLK_RIGHT:
                        {
                            LOG_INFO() << "Pressed right\n";
                            break;
                        }
                    }
                    break;
                }
            }
        }

        return true;
    }
}

