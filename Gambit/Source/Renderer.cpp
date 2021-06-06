#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Vector2.hpp"

namespace Gambit
{
    Renderer::Renderer()
    {
        Construct("Renderer");
    }

    Renderer::~Renderer()
    {
        Destroy();
    }

    bool Renderer::Construct(const char *title)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            LOG_ERROR() << "SDL_Init" << SDL_GetError() << std::endl;
            return false;
        }

        _window = SDL_CreateWindow(title, 0, 0, Width, Height, SDL_WINDOW_SHOWN);
        if (_window == nullptr) {
            LOG_ERROR() << "SDL_CreateWindow" << SDL_GetError() << std::endl;
            return false;
        }

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (_renderer == nullptr) {
            LOG_ERROR() << "SDL_CreateRender" << SDL_GetError() << std::endl;
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

    bool Renderer::Clear()
    {
        SDL_RenderClear(_renderer);
        return true;
    }

    bool Renderer::Present()
    {
        SDL_RenderPresent(_renderer);
        return true;
    }

    bool Renderer::WriteTexture(TexturePtr texture, Vector2 const& topLeft) const
    {
        auto dest = texture->GetBounds();
        dest.top = topLeft.y;
        dest.left = topLeft.x;
        return WriteTexture(texture, nullptr, &dest);
    }

    bool Renderer::WriteTexture(TexturePtr texture, Rect const *source = nullptr, Rect const *dest = nullptr) const
    {
        SDL_Rect *srcRect = reinterpret_cast<SDL_Rect *>(const_cast<Rect *>(source));
        SDL_Rect *destRect = reinterpret_cast<SDL_Rect *>(const_cast<Rect *>(dest));
        int result = SDL_RenderCopy(_renderer, &texture->Get(), srcRect, destRect);
        if (result != 0)
        {
            LOG_ERROR() << "Failed to write texture " << texture->GetName() << ": " << SDL_GetError() << std::endl;
            return false;
        }
        
        return true;
    }
}

