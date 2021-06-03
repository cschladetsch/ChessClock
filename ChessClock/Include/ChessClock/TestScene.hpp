#pragma once

#include "Gambit/Context.hpp"

namespace Gambit::TestScene
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

