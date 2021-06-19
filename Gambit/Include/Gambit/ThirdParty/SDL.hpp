#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define CALL_SDL(X) \
    do { \
        result = (X); \
        if (result != 0 ) \
        { \
            LOG_ERROR() << #X << SDL_GetError() << "\n"; \
            return false; \
        } \
    } while (0)

