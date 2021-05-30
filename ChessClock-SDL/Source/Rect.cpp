#include "ChessClock/ThirdParty/SDL.hpp"
#include "ChessClock/Rect.hpp"

namespace ChessClock
{
    Rect::Rect() 
    { 
    }

    Rect::Rect(int t, int l, int w, int h)
        : top(t), left(l), width(w), height(h)
    {
    }
}
