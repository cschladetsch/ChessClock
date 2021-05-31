#include "Gambit/Font.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/TestScene.hpp"
#include "Gambit/NumberFont.hpp"

namespace Gambit::TestScene
{
    Logger _log{ "Scene" };

    struct Values
    {
        FontPtr font;
        TexturePtr background;
        TexturePtr text;
        NumberFont numberFont;
        Rect bounds;
    };

    bool Setup(Context<Values> &ctx)
    {
        ctx.values = std::make_shared<Values>();
        Renderer &renderer = ctx.renderer;
        ResourceManager &resources = ctx.resources;

        ctx.values->font = resources.CreateResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
        ctx.values->numberFont = resources.CreateResource<NumberFont>("AdobeFanHeitiStd-Bold.otf", 100);
        ctx.values->background = resources.CreateResource<Texture>("sample.bmp", &renderer, 800, 480);
        ctx.values->text = ctx.values->font->DrawText(resources, renderer, "Hello world", { 255,255,255 });
        ctx.values->bounds = ctx.values->text->GetBounds();

        ctx.steps.push_back(StepWriteBackground);
        ctx.steps.push_back(StepWriteText);
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
