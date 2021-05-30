#pragma once

#include "ChessClock/Resource.hpp"

namespace ChessClock
{
    class Texture : public Resource<SDL_Texture>
    {
    public:
        Texture(ResourceId const& rid, SDL_Texture *texture)
            : Resource<SDL_Texture>(texture, rid, Deleter)
        {
        }

        static void Deleter(SDL_Texture* font);

        template <class ...Args>
        static shared_ptr<Texture> Load(std::string const &fileNname, ResourceId const &id, Args... args)
        {
            int width = std::get<0>(std::tuple{ args... });
            int height = std::get<1>(std::tuple{ args... });
            return LoadTexture(fileName, id, pointSize);
        }
        static shared_ptr<Texture> LoadTexture(std::string const& fileName, ResourceId const& id, int width, int height);
    };

    template <>
    struct ResourceLoader<Texture> : ResourceLoaderBase
    {
        template <class ...Args>
        static std::shared_ptr<Texture> Load(std::string const& fileName, Args... args)
        {
            return Texture::Load(fileName, args...);
        }
    };
}
