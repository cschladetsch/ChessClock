#pragma once

#include "Gambit/Context.hpp"
#include "Gambit/Logger.hpp"

namespace ChessClock
{
    class MainScene
    {
        static inline Gambit::Logger _log{ "MainScene" };

    public:
        struct Values;
        typedef Gambit::Context<Values> Ctx;

        MainScene() = default;
        bool Setup(Ctx &);
        bool Step(Ctx &);
        bool ProcessEvents(Ctx &);
        bool StepWriteText(Ctx &);
        bool StepPresent(Ctx &);
        bool StepWriteTimers(Ctx& ctx);
        bool StepWriteBackground(Ctx& ctx);
    };
}

