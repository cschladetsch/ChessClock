#pragma once

#include "ChessClock/TimeControl.hpp"

namespace ChessClock
{
    class PlayerTime
    {
        TimeControl _timeControl;
        TimeControl _remaining;
        TimeUnit _incrementSeconds{ 0 };

    public:
        PlayerTime(int minutes, int seconds, int incrementSeconds = 0)
            : _timeControl(minutes, seconds), _remaining(minutes, seconds)
            , _incrementSeconds(incrementSeconds)
        {
        }

        Minutes GetMinutes() const { return _remaining.GetMinutes(); }
        Seconds GetSeconds() const { return _remaining.GetSeconds(); }

        void Reset() { Reset(_timeControl); }
        void Reset(TimeControl timeControl) { _remaining = _timeControl = timeControl; }
        bool IsPositive() const { return _remaining.IsPositive(); }

        void Add(MilliSeconds millis) { _remaining.AddMillis(millis); }
        void Subtract(MilliSeconds millis) { Add(-millis); }
    };

    TimeUnit TimeNow();
}
