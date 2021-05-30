#pragma once

#include "ChessClock/Resource.hpp"
#include "ChessClock/Rect.hpp"

namespace ChessClock
{
    class Texture
        : public Resource<SDL_Texture>
    {
        static inline Logger _log{ "Texture" };

    public:
        Texture(ResourceId const& id, SDL_Texture *texture)
            : Resource<SDL_Texture>(texture, id, Deleter)
        {
        }

        static void Deleter(SDL_Texture* font);

        template <class ...Args>
        static shared_ptr<Texture> Load(std::string const &fileName, ResourceId const &id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            Renderer const *renderer = std::get<0>(tuple);
            int width = std::get<1>(tuple);
            int height = std::get<2>(tuple);
            LOG_DEBUG() << "Loading" << LOG_VALUE(fileName) << LOG_VALUE(width) << LOG_VALUE(height) << std::endl;
            return LoadTexture(fileName, id, *renderer, width, height);
        }

        static shared_ptr<Texture> LoadTexture(std::string const& fileName, ResourceId const& id, Renderer const &renderer, int width, int height);

        Rect GetBounds() const;
    };
}
