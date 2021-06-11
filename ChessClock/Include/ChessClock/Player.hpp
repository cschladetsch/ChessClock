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

    struct PlayerTime
    {
        int hours{ 0 }, minutes{ 0 }, seconds{ 0 }, millis{ 0 };

        void Subtract(float seconds);

        bool IsPositive() const { return hours > 0 && minutes > 0 && seconds > 0 && millis > 0; }
    };

    class Player
    {
        bool _paused{ true };

    public:
        string Name;
        PlayerTime RemainingTime;
        int IncrementSeconds{ 0 };
        EColor Color{ EColor::None };

    public:
        Player() {}

        void Pause(bool paused = true);
        void UpdateTime(float deltaSeconds);
    };
}
