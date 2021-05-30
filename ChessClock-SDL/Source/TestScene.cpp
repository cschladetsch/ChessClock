#include "ChessClock/TestScene.hpp"
#include "ChessClock/Font.hpp"
#include "ChessClock/Texture.hpp"

namespace ChessClock::TestScene
{
    Logger _log{ "TestScene" };

    bool TestSetup(Context<Values> &ctx)
    {
        Renderer& renderer = ctx.renderer;
        ResourceManager& resources = ctx.resources;

        ctx.values.font = resources.CreateResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
        ctx.values.background = resources.CreateResource<Texture>("sample.bmp", &renderer, 800, 480);
        ctx.values.text = ctx.values.font->DrawText(resources, renderer, "Hello world", { 255,255,255 });
        ctx.values.bounds = ctx.values.text->GetBounds();

        return true;
    }

    bool TestStep(Context<Values>& ctx)
    {
        Renderer& renderer = ctx.renderer;
        Values& values = ctx.values;

        renderer.Clear();
        renderer.WriteTexture(values.background, nullptr, nullptr);
        renderer.WriteTexture(values.text, nullptr, &values.bounds);
        renderer.Present();

        return true;
    }

    bool TestProcessEvents(Context<Values> &ctx)
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
