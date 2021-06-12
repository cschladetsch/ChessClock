#include "ChessClock/PlayerTime.hpp"

namespace ChessClock
{
    TimeUnit TimeNow()
    {
        return (TimeUnit)SDL_GetTicks();
    }
}
