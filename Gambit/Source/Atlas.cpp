#include "Gambit/ThirdParty/SDL.hpp"
#include "ChessClock/Atlas.hpp"
#include "SDL_image.h"

namespace ChessClock
{
    using namespace Gambit;

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
