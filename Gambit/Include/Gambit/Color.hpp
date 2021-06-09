#pragma once

#include "Gambit/Config.hpp"

namespace Gambit
{
    struct Color
    {
        typedef uint8_t Channel;

        // default to hotpink
        Channel red{ 0xff };
        Channel green{ 0x69 };
        Channel blue{ 0xb4 };
        Channel alpha{ 0xff };

        Color() { }
        Color(Channel r, Channel g, Channel b, Channel a = 0xff)
            : red(r), green(g), blue(b), alpha(a)
        {
        }

        friend bool operator==(Color const& left, Color const& right)
        {
            return left.red == right.red && left.green == right.green && left.blue == right.blue && left.alpha == right.alpha;
        }
    };
}

namespace std
{
    template <>
    struct hash<Gambit::Color>
    {
		inline size_t operator()(const Gambit::Color& color) const
        {
            return *reinterpret_cast<const uint32_t *>(&color);
        }
    };

}
