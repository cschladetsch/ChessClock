#pragma once

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/EGameState.hpp"
#include "ChessClock/PlayerTime.hpp"
#include "ChessClock/EColor.hpp"

namespace ChessClock
{
    class Player
    {
        static inline Logger _log{ "Player" };

        string _name;
        bool _paused{ true };
        int IncrementSeconds{ 0 };
        EColor _color{ EColor::None };
        PlayerTime _remainingTime{ 0,0,0 };

    public:
        Player() {}

        string GetName() const { return _name; }
        void SetName(string name) { _name = name; }

        EColor GetColor() const { return _color; }

        bool IsPaused() const { return _paused; }

        Minutes GetMinutes() const { return _remainingTime.GetMinutes(); }
        Seconds GetSeconds() const { return _remainingTime.GetSeconds(); }
        TimeUnit HasTimedOut() const { return !_remainingTime.IsPositive(); }

    protected:
        friend class Game;

        void SetColor(EColor color) { _color = color; }
        void Pause(bool paused = true);
        void SetTimeControl(TimeControl timeControl);
        void AddMillis(MilliSeconds millis) { _remainingTime.Add(millis); }
    };
}
