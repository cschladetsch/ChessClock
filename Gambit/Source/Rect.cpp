#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Rect.hpp"

namespace Gambit
{
    Rect::Rect(int t, int l, int w, int h)
        : top(t), left(l), width(w), height(h)
    {
    }
}


std::ostream& operator<<(std::ostream& s, Gambit::Rect const &rc)
{
    return s << '[' << rc.left << ", " << rc.top << ", " << rc.width << ", " << rc.height << ']';
}
