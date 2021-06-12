#pragma once

#include <stdint.h>

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
        Minutes GetMinutes() const { return GetTotalSeconds() / 60; }
        Seconds GetSeconds() const { return GetTotalSeconds() % 60; }
        MilliSeconds GetMillis() const { return _totalMillis % 1000; }

        void AddMillis(MilliSeconds millis) { _totalMillis += millis; }

        bool IsPositive() const { return _totalMillis > 0; }
        bool HasTimedOut() const { return !IsPositive(); }
    };
}

