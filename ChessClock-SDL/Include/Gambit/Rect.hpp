#pragma once

#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    struct Rect
    {
        int top{ 0 }, left{ 0 }, width{ 0 }, height{ 0 };

        Rect();
        Rect(int top, int left, int width, int height);
    };
}
