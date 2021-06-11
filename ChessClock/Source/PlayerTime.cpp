#include "ChessClock/PlayerTime.hpp"

namespace ChessClock
{
    TimeUnit TimeNow()
    {
        return (TimeUnit)SDL_GetTicks();
    }

    void PlayerTime::Add(MilliSeconds millisConsumed)
    {
        if (millisConsumed > 0)
            millis += millisConsumed;
        else
            millis -= millisConsumed;

        seconds = millis / 1000;
        minutes = seconds / 60;
    }
}
