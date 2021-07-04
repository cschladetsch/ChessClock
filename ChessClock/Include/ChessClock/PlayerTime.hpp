#pragma once

#include "Gambit/Time.hpp"

#include "ChessClock/TimeControl.hpp"

namespace ChessClock
{
    class PlayerTime
    {
        TimeControl _timeControl;
        TimeControl _remaining;

    public:
        PlayerTime(int minutes, int seconds, int incrementSeconds = 0)
            : _timeControl(minutes, seconds, incrementSeconds), _remaining(minutes, seconds)
        { }

        TimeControl const &GetTimeRemaining() const { return _remaining; }

        Gambit::Minutes GetMinutes() const { return _remaining.GetMinutes(); }
        Gambit::Seconds GetSeconds() const { return _remaining.GetSeconds(); }
        Gambit::Seconds GetIncrement() const { return _timeControl.GetIncrement(); }

        void Reset() { Reset(_timeControl); }
        void Reset(TimeControl timeControl) { _remaining = _timeControl = timeControl; }
        bool IsPositive() const { return _remaining.IsPositive(); }
        void AddMillis(Gambit::MilliSeconds millis) { _remaining.AddMillis(millis); }
        void Subtract(Gambit::MilliSeconds millis) { AddMillis(-millis); }

        void SetTimeControl(TimeControl const &timeControl)
        {
            _remaining = _timeControl = timeControl;
        }
    };
}

