#pragma once

#include "Gambit/Rect.hpp"

namespace ChessClock
{
    struct Global
    {
        explicit Global(const Gambit::Rect& screenRect)
            : ScreenRect(screenRect)
        {
        }

        const Gambit::Rect ScreenRect;

        int GetScreenWidth() const { return ScreenRect.width; }
        int GetScreenHeight() const { return ScreenRect.height; }
    };

    extern Global global;
}

