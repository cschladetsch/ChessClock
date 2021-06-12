#pragma once

#include <ostream>

namespace ChessClock
{
    enum class ESide
    {
        Left,
        Right
    };

    inline std::ostream& operator<<(std::ostream& out, ESide side)
    {
        if (side == ESide::Left)
            return out << "Left";
        return out << "Right";
    }
}
