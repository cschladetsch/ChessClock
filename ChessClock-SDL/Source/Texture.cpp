#include "ChessClock/SDL.hpp"
#include "ChessClock/Texture.hpp"
#include "ChessClock/Renderer.hpp"
#include "ChessClock/Rect.hpp"

namespace ChessClock
{
    shared_ptr<Texture> Texture::LoadTexture(std::string const& fileName, ResourceId const& id, Renderer const &renderer, int width, int height)
    {
        SDL_Surface *surface = SDL_LoadBMP(fileName.c_str());
        if (surface == nullptr) {
            LOG_ERROR() << "SDL_LoadBMP: " << SDL_GetError() << std::endl;
            return 0;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        if (texture == nullptr) {
            LOG_ERROR() << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(surface);
            return 0;
        }
        SDL_FreeSurface(surface);

        return std::make_shared<Texture>(id, texture);
    }

    void Texture::Deleter(SDL_Texture *texture)
    {
        SDL_DestroyTexture(texture);
    }

    Rect Texture::GetBounds() const
    {
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(const_cast<SDL_Texture *>(&Get()), nullptr, nullptr, &texW, &texH);
        return { 0, 0, texW, texH };
    }

}
