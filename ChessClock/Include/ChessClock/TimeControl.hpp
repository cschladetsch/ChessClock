#pragma once

#include "Gambit/Time.hpp"

#undef max

namespace ChessClock
{
    class TimeControl
    {
        Gambit::MilliSeconds _totalMillis{ 0 };
        Gambit::Seconds _increment{ 0 };

    public:
        TimeControl() = default;
        TimeControl(TimeControl const &) = default;

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

        void AddMillis(Gambit::MilliSeconds millis) { AddMillisEx(millis); } 
        void AddSeconds(Gambit::Seconds seconds) { AddMillis(seconds*1000); } 
        void AddMinutes(Gambit::Minutes minutes) { AddSeconds(minutes * 60); }

        void AddIncrementSeconds(Gambit::Seconds seconds) { _increment = std::max(Gambit::MilliSeconds{0}, _increment + seconds); }

        bool IsPositive() const { return _totalMillis > 0; }
        bool HasTimedOut() const { return !IsPositive(); }

    private:
        void AddMillisEx(Gambit::MilliSeconds millis)
        {
            _totalMillis = std::max(Gambit::MilliSeconds{ 0 }, _totalMillis + millis);
        }
    };
}

