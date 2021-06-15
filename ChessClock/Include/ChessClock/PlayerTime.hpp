#pragma once

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
        {
        }

        Minutes GetMinutes() const { return _remaining.GetMinutes(); }
        Seconds GetSeconds() const { return _remaining.GetSeconds(); }
        Seconds GetIncrement() const { return _timeControl.GetIncrement(); }

        void Reset() { Reset(_timeControl); }
        void Reset(TimeControl timeControl) { _remaining = _timeControl = timeControl; }

        bool IsPositive() const { return _remaining.IsPositive(); }

        void AddMillis(MilliSeconds millis) { _remaining.AddMillis(millis); }
        void Subtract(MilliSeconds millis) { AddMillis(-millis); }
    };

    TimeUnit TimeNow();
}

