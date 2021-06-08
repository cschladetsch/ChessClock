#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Atlas.hpp"
#include "SDL_image.h"

namespace Gambit
{
    Atlas::Atlas(SDL_Surface *surface, const string &spritsJson)
    {
    }

    shared_ptr<Atlas> Atlas::LoadAtlas(ResourceId const& id, string const& baseName)
    {
        string fileName = baseName + ".png";
        string spritesName = baseName + ".json";

        SDL_Surface *surface = IMG_Load(fileName.c_str());
        if (!surface)
        {
            LOG_ERROR() << "Failed to load " << fileName << "\n";
        }

        return std::make_shared<Atlas>(surface, spritesName);
    }
}
