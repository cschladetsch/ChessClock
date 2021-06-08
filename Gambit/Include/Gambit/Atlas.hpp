#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    class Atlas
        : public ResourceBase
    {
        static inline Logger _log{ "Atlas" };
        TexturePtr _texture;

    public:
        Atlas(SDL_Surface *surface, const string &spritsJson);

        template <class ...Args>
        static shared_ptr<Atlas> Load(std::string const& baseName, ResourceId const& id, Args... args)
        {
            return LoadAtlas(id, baseName);
        }

    private:
        static shared_ptr<Atlas> LoadAtlas(ResourceId const& id, string const& baseName);
    };
}
