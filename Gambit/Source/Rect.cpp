#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Rect.hpp"

namespace Gambit
{
    Rect::Rect() 
    { 
    }

    Rect::Rect(int t, int l, int w, int h)
        : top(t), left(l), width(w), height(h)
    {
    }
}
