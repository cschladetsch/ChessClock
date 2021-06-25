#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Rect.hpp"

namespace Gambit
{
    Rect::Rect(int t, int l, int w, int h)
        : top(t), left(l), width(w), height(h)
    {
    }

    bool Rect::Contains(Vector2 where) const
    {
        if (where.x < left)
            return false;
        if (where.x > left + width)
            return false;
        if (where.y < top)
            return false;
        return where.y <= top + height;
    }
}

