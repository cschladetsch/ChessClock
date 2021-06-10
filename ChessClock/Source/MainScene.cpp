#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/MainScene.hpp"
#include "ChessClock/Game.hpp"
#include "ChessClock/Global.hpp"

namespace ChessClock
{
    using namespace Gambit;

    struct MainScene::Values
    {
        FontPtr font;
        TexturePtr backBuffer;
        TexturePtr background;
        TexturePtr text;
        Rect textBounds;
        NumberFontPtr numberFont;
        AtlasPtr atlas;
        Game game;
    };

    bool MainScene::Setup(Context& ctx)
    {
        ctx.values = std::make_shared<Values>();
        Renderer& renderer = ctx.renderer;
        ResourceManager& resources = ctx.resources;
        auto& values = *ctx.values;

        values.font = resources.LoadResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
        values.background = resources.LoadResource<Texture>("sample.bmp", &renderer, global.ScreenWidth(), global.ScreenHeight());
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,0 });
        values.text = values.font->CreateTexture(resources, renderer, "Hello world", { 255,255,255 });
        values.textBounds = values.text->GetBounds();
        values.atlas = resources.LoadResource<Atlas>("Lichess\\atlas", resources, &renderer);

        AddStep(ctx, &MainScene::StepWriteBackground);
        //AddStep(ctx, &MainScene::StepWriteText);
        //AddStep(ctx, &MainScene::StepWriteTimers);
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
        return atlas->WriteSprite(renderer, "background", Rect{ 0,0,800,480 });
    }

    bool MainScene::StepWriteText(Context &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->text, nullptr, &ctx.values->textBounds);
    }

    bool MainScene::StepWriteTimers(Context &ctx)
    {
        Vector2 destPoint{ 100, 100 };
        uint32_t millis = SDL_GetTicks();
        uint32_t seconds = millis / 1000;
        uint32_t minutes = seconds / 60;
        ctx.values->numberFont->DrawTime(ctx.renderer, destPoint, minutes%60, seconds%60, millis%10);
        return true;
    }

    bool MainScene::StepPresent(Context &ctx)
    {
        return ctx.renderer.Present();
    }

    bool MainScene::ProcessEvents(Context &ctx)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                {
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                        {
                            Vector2 where{ event.button.x, event.button.y };
                            LOG_INFO() << "Pressed " << where << "\n";
                            break;
                        }
                    }
                    break;
                }

                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        {
                            LOG_INFO() << "Pressed Escape\n";
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

