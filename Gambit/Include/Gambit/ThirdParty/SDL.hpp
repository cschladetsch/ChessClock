#pragma once

#include "SDL.h"

#define CALL_SDL(X) \
    do { \
        result = (X); \
        if (result != 0 )\
        {\
            LOG_ERROR() << #X << "Error: " << SDL_GetError() << "\n"; \
            return false; \
        } \
    } while (0)
