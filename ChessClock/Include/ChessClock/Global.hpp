#pragma once

#include "ChessClock/Config.hpp"
#include "Gambit/Rect.hpp"

namespace ChessClock
{
    struct Global
    {
        explicit Global(Rect& screenRect)
            : ScreenRect(screenRect)
        {
        }

        const Rect ScreenRect;

        int GetScreenWidth() const { return ScreenRect.width; }
        int GetScreenHeight() const { return ScreenRect.height; }
    };

    extern Global global;
}
