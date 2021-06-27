#pragma once

#include <cstdint>

#include "Gambit/Time.hpp"

namespace ChessClock
{
    class TimeControl
    {
        Gambit::MilliSeconds _totalMillis{ 0 };
        Gambit::Seconds _increment;

    public:
        TimeControl(Gambit::Minutes minutes, Gambit::Seconds seconds, Gambit::Seconds increment = 0)
            : _increment(increment)
        {
            _totalMillis = (minutes * 60 + seconds) * 1000;
        }

        Gambit::Minutes GetMinutes() const { return GetTotalSeconds() / 60; }
        Gambit::Seconds GetSeconds() const { return GetTotalSeconds() % 60; }
        Gambit::MilliSeconds GetMillis() const { return _totalMillis % 1000; }

        Gambit::Seconds GetTotalSeconds() const { return _totalMillis / 1000; }
        Gambit::Seconds GetIncrement() const { return _increment; }

        void AddMillis(Gambit::MilliSeconds millis) { _totalMillis += millis; } 
        bool IsPositive() const { return _totalMillis > 0; }
        bool HasTimedOut() const { return !IsPositive(); }
    };
}

