#pragma once

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/EGameState.hpp"
#include "ChessClock/PlayerTime.hpp"
#include "ChessClock/EColor.hpp"

namespace ChessClock
{
    class Player
        : Gambit::NonCopyable
    {
        static inline Logger _log{ "Player" };

        string _name;
        bool _paused{ true };
        EColor _color{ EColor::None };
        PlayerTime _remainingTime{ 0,0,0 };
        ObjectPtr _object;

    public:
        string GetName() const { return _name; }
        void SetName(string name) { _name = name; }

        EColor GetColor() const { return _color; }

        bool IsPaused() const { return _paused; }

        Minutes GetMinutes() const { return _remainingTime.GetMinutes(); }
        Seconds GetSeconds() const { return _remainingTime.GetSeconds(); }
        TimeUnit HasTimedOut() const { return !_remainingTime.IsPositive(); }
        Seconds GetIncrement() const { return _remainingTime.GetIncrement(); }

    protected:
        friend class GamePlaying;

        void SetColor(EColor color) { _color = color; }
        void Pause(bool paused = true);
        void SetTimeControl(TimeControl timeControl);
        void AddMillis(MilliSeconds millis) { _remainingTime.AddMillis(millis); }
        void AddSeconds(Seconds seconds) { _remainingTime.AddMillis(seconds*1000); }
    };
}
