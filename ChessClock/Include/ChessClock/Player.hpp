#pragma once

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    enum class EColor
    {
        None,
        White,
        Black,
    };

    class Player
    {
    public:
        std::string Name;
        int MillisRemaining{ 0 };
        int MillisIncrement{ 0 };
        EColor Color{ EColor::None };

    public:
        Player() {}
    };
}
