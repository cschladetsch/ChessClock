#pragma once

#include "Gambit/ResourceManager.hpp"
#include "Gambit/Rect.hpp"

namespace Gambit
{
    class Sprite
    {
        Rect _rect;

    public:
        Sprite(ResourceManager &, const char *name, Rect const &rect);
    };
}
