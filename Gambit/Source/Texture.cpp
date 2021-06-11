#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Rect.hpp"

namespace Gambit
{
    shared_ptr<Texture> Texture::LoadTexture(std::string const& fileName, ResourceId const& id, Renderer const &renderer, int width, int height)
    {
        SDL_Surface *surface = SDL_LoadBMP(fileName.c_str());
        if (surface == nullptr) {
            LOG_ERROR() << "SDL_LoadBMP: " << LOG_VALUE(SDL_GetError()) << std::endl;
            return 0;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        if (texture == nullptr) {
            LOG_ERROR() << "SDL_CreateTextureFromSurface: " << LOG_VALUE(SDL_GetError()) << std::endl;
            SDL_FreeSurface(surface);
            return 0;
        }
        SDL_FreeSurface(surface);
        LOG_INFO() << "Created texture " << LOG_VALUE(fileName) << LOG_VALUE(id) << "\n";

        return std::make_shared<Texture>(id, texture);
    }

    void Texture::Deleter(SDL_Texture *texture)
    {
        LOG_INFO() << "Deleting texture " << texture << "\n";
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
