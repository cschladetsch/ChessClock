#include "ChessClock/Texture.hpp"
#include "ChessClock/SDL.hpp"

namespace ChessClock
{
    shared_ptr<Texture> Texture::LoadTexture(std::string const& fileName, ResourceId const& id, int width, int height)
    {
        return 0;
    }

    void Texture::Deleter(SDL_Texture *texture)
    {
        SDL_DestroyTexture(texture);
    }

}
