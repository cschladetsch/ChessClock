#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Atlas.hpp"
#include "SDL_image.h"

namespace Gambit
{
    bool Atlas::Load(const char* fileName)
    {
        SDL_Surface *surface = IMG_Load(fileName);

        if (!surface)
        {
            LOG_ERROR() << "Failed to load " << fileName << "\n";
        }
        return true;
    }
}
