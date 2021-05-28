#include "ChessClock/Renderer.hpp"

namespace ChessClock
{
    Renderer::Renderer()
    {
    }

    bool Renderer::Construct()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            LOG_ERROR() << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        _window = SDL_CreateWindow("World!", 100, 100, 620, 387, SDL_WINDOW_SHOWN);
        if (_window == nullptr) {
            LOG_ERROR() << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return false;
        }

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (_renderer == nullptr) {
            LOG_ERROR() << "SDL_CreateRenderer Error" << SDL_GetError() << std::endl;
            SDL_DestroyWindow(_window);
            SDL_Quit();
            return false;
        }

        return true;
    }

    void Renderer::Destroy()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
    }

    void Renderer::Clear()
    {
        SDL_RenderClear(_renderer);
    }

    void Renderer::Present()
    {
        SDL_RenderPresent(_renderer);
    }
}

