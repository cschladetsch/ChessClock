#pragma once

#include "ChessClock/EGameState.hpp"
#include "ChessClock/PlayerTime.hpp"

namespace ChessClock
{
    class Player
    {
        static inline Logger _log{ "Player" };
        bool _paused{ true };

    public:
        string Name;
        PlayerTime _remainingTime{ 0,0,0 };
        int IncrementSeconds{ 0 };
        EColor _color{ EColor::None };
        WallClockTimeMillis _timedOutTime{ 0 };
        bool _timedOut{ false };

    public:
        Player() {}

        Minutes GetMinutes() const { return _remainingTime.GetMinutes(); }
        Seconds GetSeconds() const { return _remainingTime.GetSeconds(); }

        EColor GetColor() const { return _color; }
        void Pause(bool paused = true);
        void UpdateTime(MilliSeconds millisConsumed);
        bool TimedOut() const { return _timedOut; }
        TimeUnit TimedOutTime() const { return _timedOutTime; }

    protected:
        friend class Game;

        void SetTimeControl(TimeControl timeControl);
        void SetColor(EColor color) { _color = color; }
    };
}
