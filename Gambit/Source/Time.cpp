#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Time.hpp"

namespace Gambit
{
    TimeUnit TimeNowMillis()
    {
        return static_cast<TimeUnit>(SDL_GetTicks());
    }

    float TimeNowSeconds()
    {
        return static_cast<float>(TimeNowMillis())/1000.f;
    }
}
