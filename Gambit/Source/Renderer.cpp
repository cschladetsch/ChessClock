#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/Color.hpp"

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
        int result = 0;
        CALL_SDL(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO));

        _window = SDL_CreateWindow(title, 0, 0, Width, Height, SDL_WINDOW_SHOWN);
        if (_window == nullptr)
        {
            LOG_ERROR() << "SDL_CreateWindow" << SDL_GetError() << std::endl;
            return false;
        }

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (_renderer == nullptr)
        {
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
        CALL_SDL(SDL_RenderClear(_renderer));
        return true;
    }

    bool Renderer::Present()
    {
        SDL_RenderPresent(_renderer);
        ++_frameNumber;
        return true;
    }

    bool Renderer::WriteTexture(TexturePtr const &texture, Vector2 const& topLeft, Gambit::Color const &tint) const
    {
        CALL_SDL(SDL_SetTextureColorMod(&texture->Get(), tint.red, tint.green, tint.blue));
        CALL(WriteTexture(texture, topLeft));
        CALL_SDL(SDL_SetTextureColorMod(&texture->Get(), 255, 255, 255));
        return true;
    }

    bool Renderer::WriteTexture(TexturePtr const &texture, Vector2 const& topLeft) const
    {
        auto dest = texture->GetBounds();
        dest.left = topLeft.y;
        dest.top = topLeft.x;
        return WriteTexture(texture, nullptr, &dest);
    }

    bool Renderer::WriteTexture(TexturePtr const &texture, Rect const *source = nullptr, Rect const *dest = nullptr) const
    {
        const auto srcRect = reinterpret_cast<SDL_Rect *>(const_cast<Rect *>(source));
        const auto destRect = reinterpret_cast<SDL_Rect *>(const_cast<Rect *>(dest));
        CALL_SDL(SDL_RenderCopy(_renderer, &texture->Get(), srcRect, destRect));
        return true;
    }
}

