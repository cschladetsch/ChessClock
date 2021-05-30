#define SDL_MAIN_HANDLED
#include <cstdlib>
#include <iostream>

#include "ChessClock/Logger.hpp"
#include "ChessClock/Renderer.hpp"
#include "ChessClock/Font.hpp"
#include "ChessClock/Texture.hpp"
#include "ChessClock/ResourceManager.hpp"

using namespace ChessClock;

int main(int argc, char **argv)
{
    Logger _log{ "Main" };
    Renderer renderer;
    if (argc < 2)
    {
        LOG_ERROR() << "Resources folder required\n";
        return 1;
    }
    const char* resourcesFolder = argv[1];

    if (!renderer.Construct())
    {
        LOG_ERROR() << "Failed to initialise Renderer\n";
        return 1;
    }


    ResourceManager resourceManager(renderer, resourcesFolder);

    shared_ptr<Font> font = resourceManager.CreateResource<Font>("AdobeFanHeitiStd-Bold.otf", 100);
    if (!font->Exists())
    {
        LOG_ERROR() << "Couldn't load font\n";
        exit(1);
    }
    //std::shared_ptr<Resource<Texture>> texture = resourceManager.CreateResource<Texture>("sample.bmp");

    SDL_Surface* bmp = SDL_LoadBMP("sample.bmp");
    if (bmp == nullptr) {
        LOG_ERROR() << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* ren = renderer.GetRenderer();

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer.GetRenderer(), bmp);
    if (tex == nullptr) {
        LOG_ERROR() << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(bmp);
        renderer.Destroy();
        SDL_Quit();
        return 1;
    }
    SDL_FreeSurface(bmp);

    SDL_Color color = { 255, 255, 255 };
    auto text = font->DrawText(resourceManager, renderer, "Hello world", color);

    while (true)
    {
        renderer.Clear();
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(&text->Get(), NULL, NULL, &texW, &texH);
        SDL_Rect dest = { 0, 0, texW, texH };
        SDL_RenderCopy(ren, &text->Get(), 0, &dest);

        renderer.Present();

        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            exit(0);
            break;
        }
    }

    SDL_DestroyTexture(tex);

    renderer.Destroy();
    SDL_Quit();

    return 0;
}
