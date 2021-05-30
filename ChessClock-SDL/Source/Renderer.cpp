#include "ChessClock/Renderer.hpp"
#include "ChessClock/Texture.hpp"
#include "ChessClock/SDL.hpp"

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

    bool Renderer::WriteTexture(TexturePtr texture, Rect const *source, Rect const *dest) const
    {
        SDL_Rect* srcRect = reinterpret_cast<SDL_Rect*>(const_cast<Rect *>(source));
        SDL_Rect* destRect = reinterpret_cast<SDL_Rect*>(const_cast<Rect *>(dest));
        int result = SDL_RenderCopy(_renderer, &texture->Get(), srcRect, destRect);
        if (result != 0)
        {
            LOG_ERROR() << "Failed to render texture " << texture->GetName() << ": " << SDL_GetError() << std::endl;
            return false;
        }
        
        return true;
    }
}

