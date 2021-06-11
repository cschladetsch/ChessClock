#pragma once

#include <ostream>
#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    enum class EColor
    {
        None,
        White,
        Black,
    };

    enum class ESide
    {
        Left,
        Right
    };

    enum class EGameState
    {
        None,
        Ready,
        Playing,
        Paused,
        Draw,
        WhiteWon,
        BlackWon,
    };

    inline std::ostream& operator<<(std::ostream& out, EGameState state)
    {
        switch (state)
        {
        case EGameState::None:
            return out << "None";
        case EGameState::Ready:
            return out << "Ready";
        case EGameState::Playing:
            return out << "Playing";
        case EGameState::Paused:
            return out << "Paused";
        case EGameState::Draw:
            return out << "Draw";
        case EGameState::WhiteWon:
            return out << "WhiteWon";
        case EGameState::BlackWon:
            return out << "BlackWon";
        }

        return out << "Unknown game state " << (int)state;
    }

    inline std::ostream& operator<<(std::ostream& out, EColor color)
    {
        if (color == EColor::White)
            return out << "White";
        return out << "Black";
    }
}
