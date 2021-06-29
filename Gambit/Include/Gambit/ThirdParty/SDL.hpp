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
        _result = (X); \
        if (_result != 0 ) \
        { \
            LOG_ERROR() << #X << LOG_VALUE(SDL_GetError()) << "\n"; \
        } \
    } while (0)

