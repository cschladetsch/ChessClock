#include "Gambit/Font.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/NumberFont.hpp"

#include "ChessClock/TestScene.hpp"
#include "ChessClock/Game.hpp"

namespace ChessClock::TestScene
{
    using namespace Gambit;

    Logger _log{ "Scene" };

    struct Values
    {
        FontPtr font;
        TexturePtr background;
        TexturePtr text;
        NumberFontPtr numberFont;
        Rect bounds;

        Game game;
    };

    bool Setup(Context<Values> &ctx)
    {
        ctx.values = std::make_shared<Values>();
        Renderer &renderer = ctx.renderer;
        ResourceManager &resources = ctx.resources;
        auto& values = *ctx.values;

        values.font = resources.LoadResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
        values.background = resources.LoadResource<Texture>("sample.bmp", &renderer, 800, 480);
        values.numberFont = resources.CreateResource<NumberFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,0 });
        values.text = ctx.values->font->DrawText(resources, renderer, "Hello world", { 255,255,255 });
        values.bounds = ctx.values->text->GetBounds();

        ctx.steps.push_back(StepWriteBackground);
        ctx.steps.push_back(StepWriteText);
        ctx.steps.push_back(StepWriteTimers);
        ctx.steps.push_back(StepPresent);

        return true;
    }

    bool Step(Context<Values> &ctx)
    {
        return ctx.renderer.Clear();
    }

    bool StepWriteBackground(Ctx &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->background, nullptr, nullptr);
    }

    bool StepWriteText(Ctx &ctx)
    {
        return ctx.renderer.WriteTexture(ctx.values->text, nullptr, &ctx.values->bounds);
    }

    bool StepWriteTimers(Ctx &ctx)
    {
        Vector2 destPoint{ 100, 100 };
        uint32_t millis = SDL_GetTicks();
        uint32_t seconds = millis / 1000;
        uint32_t minutes = seconds / 60;
        ctx.values->numberFont->DrawTime(ctx.renderer, destPoint, minutes, seconds, millis);
        return true;
    }

    bool StepPresent(Ctx &ctx)
    {
        return ctx.renderer.Present();
    }

    bool ProcessEvents(Ctx &ctx)
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
