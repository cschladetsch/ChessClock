#define SDL_MAIN_HANDLED

#include <cstdlib>
#include <iostream>

#include "ChessClock/Logger.hpp"
#include "ChessClock/Renderer.hpp"
#include "ChessClock/Font.hpp"
#include "ChessClock/Texture.hpp"
#include "ChessClock/ResourceManager.hpp"
#include "ChessClock/SDL_ttf.hpp"
#include "ChessClock/Context.hpp"
#include "ChessClock/Rect.hpp"

using namespace ChessClock;

struct Values
{
    FontPtr font;
    TexturePtr background;
    TexturePtr text;
    Rect bounds;
};

bool Setup(Context<Values> &ctx)
{
    Renderer& renderer = ctx.Renderer;
    ResourceManager& resources = ctx.Resources;

    ctx.Values.font = resources.CreateResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
    ctx.Values.background = resources.CreateResource<Texture>("sample.bmp", &renderer, 800, 480);
    ctx.Values.text = ctx.Values.font->DrawText(resources, renderer, "Hello world", { 255,255,255 });
    ctx.Values.bounds = ctx.Values.text->GetBounds();

    return true;
}

bool Step(Context<Values>& ctx)
{
    Renderer& renderer = ctx.Renderer;
    Values& values = ctx.Values;

    renderer.Clear();
    renderer.WriteTexture(values.background, nullptr, nullptr);
    renderer.WriteTexture(values.text, nullptr, &values.bounds);
    renderer.Present();

    return true;
}

bool ProcessEvents(Context<Values> &ctx)
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

int main(int argc, char** argv)
{
    Logger _log{ "Main" };
    if (argc < 2)
    {
        LOG_ERROR() << "Resources folder required\n";
        return 1;
    }

    return Context<Values>(argv[1], Setup, Step, ProcessEvents).Run();
}

