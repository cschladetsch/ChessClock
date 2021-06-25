#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/PlayerTime.hpp"

namespace ChessClock
{
    TimeUnit TimeNowMillis()
    {
        return (TimeUnit)SDL_GetTicks();
    }

    float TimeNowSeconds()
    {
        return (float)TimeNowMillis()/1000.f;
    }
}

