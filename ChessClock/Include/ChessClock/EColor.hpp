#pragma once

#include <ostream>

namespace ChessClock
{
    enum class EColor
    {
        None,
        White,
        Black,
    };

    inline EColor OtherColor(EColor color)
    {
        if (color == EColor::None)
            return EColor::None;
        return color == EColor::White ? EColor::Black : EColor::White;
    }

    inline std::ostream& operator<<(std::ostream& out, EColor color)
    {
        switch (color)
        {
        case EColor::None:
            return out << "None";
        case EColor::White:
            return out << "White";
        case EColor::Black:
            return out << "Black";
        }

        return out << "Unknown color " << static_cast<int>(color);
    }
}

