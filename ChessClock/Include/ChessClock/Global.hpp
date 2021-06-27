#pragma once

#include "Gambit/Rect.hpp"

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    struct Global
    {
        explicit Global(const Rect& screenRect)
            : ScreenRect(screenRect)
        {
        }

        const Rect ScreenRect;

        int GetScreenWidth() const { return ScreenRect.width; }
        int GetScreenHeight() const { return ScreenRect.height; }
    };

    extern Global global;
}

