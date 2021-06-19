#pragma once

#ifdef WIN32
    #include "SDL.h"
    #include "SDL_image.h"
#else
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
#endif

#define CALL_SDL(X) \
    do { \
        result = (X); \
        if (result != 0 ) \
        { \
            LOG_ERROR() << #X << SDL_GetError() << "\n"; \
            return false; \
        } \
    } while (0)

