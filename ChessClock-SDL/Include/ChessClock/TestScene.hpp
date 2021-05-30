#pragma once

#include "ChessClock/Context.hpp"

namespace ChessClock::TestScene
{
    struct Values;

    typedef Context<Values> Ctx;

    bool Setup(Ctx &);
    bool Step(Ctx &);
    bool ProcessEvents(Ctx &);
    bool StepWriteText(Ctx &);
    bool StepPresent(Ctx &);
    bool StepWriteBackground(Ctx& ctx);
}

