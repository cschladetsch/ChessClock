#pragma once

#include "ChessClock/Config.hpp"
#include "Gambit/Rect.hpp"

namespace ChessClock
{
    struct Global
    {
        Global(Rect& screenRect)
            : ScreenRect(screenRect)
        {
        }

        const Rect ScreenRect;

        int ScreenWidth() const { return ScreenRect.width; }
        int ScreenHeight() const { return ScreenRect.height; }
    };

    extern Global global;
}
