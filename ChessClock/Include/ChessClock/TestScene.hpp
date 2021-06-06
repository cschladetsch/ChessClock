#pragma once

#include "Gambit/Context.hpp"

namespace ChessClock::TestScene
{
    struct Values;

    typedef Gambit::Context<Values> Ctx;

    bool Setup(Ctx &);
    bool Step(Ctx &);
    bool ProcessEvents(Ctx &);
    bool StepWriteText(Ctx &);
    bool StepPresent(Ctx &);
    bool StepWriteTimers(Ctx& ctx);
    bool StepWriteBackground(Ctx& ctx);
}

