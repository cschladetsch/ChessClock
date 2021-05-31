#pragma once

#include "Gambit/Config.hpp"

namespace Gambit
{
    struct Color
    {
        typedef unsigned char Channel;
        Channel alpha;
        Channel red;
        Channel green;
        Channel blue;

        Color(Channel r, Channel g, Channel b)
            : alpha(255), red(r), green(g), blue(b)
        {
        }
    };
}
