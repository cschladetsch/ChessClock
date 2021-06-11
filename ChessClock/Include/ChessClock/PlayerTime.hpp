#pragma once

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    typedef int64_t TimeUnit, MilliSeconds, WallClockTimeMillis;

    struct TimeControl
    {
        TimeUnit minutes{ 0 }, seconds{ 0 }, millis{ 0 };
        TimeUnit IncrementSeconds;
    };

    class PlayerTime
    {
        TimeControl _timeControl;

    public:
        TimeUnit minutes{ 0 }, seconds{ 0 }, millis{ 0 };

        void Reset()
        {
            Reset(_timeControl);
        }

        void Reset(TimeControl timeControl)
        {
            _timeControl = timeControl;
            minutes = timeControl.minutes;
            seconds = timeControl.seconds;
        }

        bool IsPositive() const { return minutes > 0 || seconds > 0 || millis > 0; }

        void Add(MilliSeconds millis);
        void Subtract(MilliSeconds millis) { Add(-millis); }
    };

    TimeUnit TimeNow();
}
