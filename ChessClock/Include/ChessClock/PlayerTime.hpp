#pragma once

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    typedef int64_t TimeUnit, Minutes, Seconds, MilliSeconds, WallClockTimeMillis;

    class TimeControl
    {
        TimeUnit _totalMillis{ 0 };

    public:
        TimeControl(TimeUnit minutes, TimeUnit seconds)
        {
            _totalMillis = (minutes * 60 + seconds) * 1000;
        }

        Seconds GetTotalSeconds() const { return _totalMillis / 1000; }
        Minutes GetMinutes() const { return GetTotalSeconds()/ 60; }
        Seconds GetSeconds() const { return GetTotalSeconds() % 60; }
        MilliSeconds GetMillis() const { return _totalMillis % 1000; }

        void AddMillis(MilliSeconds millis) { _totalMillis += millis; }

        bool IsPositive() const { return _totalMillis > 0; }
    };

    class PlayerTime
    {
        TimeControl _timeControl;
        TimeControl _remaining;
        TimeUnit _incrementSeconds{ 0 };

    public:
        PlayerTime(int minutes, int seconds, int incrementSeconds = 0)
            : _timeControl(minutes, seconds), _remaining(minutes, seconds), _incrementSeconds(incrementSeconds)
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
