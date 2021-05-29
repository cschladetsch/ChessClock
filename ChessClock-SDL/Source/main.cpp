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
    const char* resourcesFolder = argc > 1 ? argv[1] : "Resources";

    if (!renderer.Construct())
    {
        LOG_ERROR() << "Failed to initialise Renderer\n";
        return 1;
    }

    ResourceManager resourceManager(renderer, resourcesFolder);

    std::shared_ptr<Resource<Texture>> texture = resourceManager.CreateResource<Texture>("sample.bmp");

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

    for (int i = 0; i < 20; i++) {
        renderer.Clear();
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        renderer.Present();
        SDL_Delay(100);
    }

    SDL_DestroyTexture(tex);
    renderer.Destroy();
    SDL_Quit();

    return 0;
}
