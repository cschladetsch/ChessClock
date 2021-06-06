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
        typedef Gambit::Context<Values> Context;

        MainScene() = default;

        bool Setup(Context &);
        bool ProcessEvents(Context &);
        bool StepWriteText(Context &);
        bool StepPresent(Context &);
        bool StepWriteTimers(Context& ctx);
        bool StepWriteBackground(Context& ctx);

    protected:
        void AddStep(Context&, bool(MainScene::*method)(Context&));
    };
}

