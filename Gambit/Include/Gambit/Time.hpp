#pragma once

#include "Gambit/Config.hpp"

namespace Gambit
{
    typedef int64_t TimeUnit, Minutes, Seconds, MilliSeconds, WallClockTimeMillis;

    TimeUnit TimeNowMillis();
    float TimeNowSeconds();
}

