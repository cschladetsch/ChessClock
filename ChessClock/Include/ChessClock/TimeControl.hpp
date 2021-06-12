#pragma once

#include <stdint.h>

namespace ChessClock
{
    typedef int64_t TimeUnit, Minutes, Seconds, MilliSeconds, WallClockTimeMillis;

    class TimeControl
    {
        MilliSeconds _totalMillis{ 0 };
        Seconds _increment;

    public:
        TimeControl(Minutes minutes, Seconds seconds, Seconds increment = 0)
            : _increment(increment)
        {
            _totalMillis = (minutes * 60 + seconds) * 1000;
        }

        Seconds GetTotalSeconds() const { return _totalMillis / 1000; }
        Minutes GetMinutes() const { return GetTotalSeconds() / 60; }
        Seconds GetSeconds() const { return GetTotalSeconds() % 60; }
        MilliSeconds GetMillis() const { return _totalMillis % 1000; }
        Seconds GetIncrement() const { return _increment; }

        void AddMillis(MilliSeconds millis) { _totalMillis += millis; } 
        bool IsPositive() const { return _totalMillis > 0; }
        bool HasTimedOut() const { return !IsPositive(); }
    };
}

