#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Time.hpp"

namespace Gambit
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
