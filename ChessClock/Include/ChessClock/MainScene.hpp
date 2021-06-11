#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Logger.hpp"

#include "ChessClock/Config.hpp"

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

        bool StepPresent(Context &);
        bool StepWriteTimers(Context& ctx);
        bool StepWriteBackground(Context& ctx);

    protected:
        void AddStep(Context&, bool(MainScene::*method)(Context&));
        void WriteButtons(Atlas const& atlas, Renderer& renderer) const;
        void WriteHeader(Atlas const& atlas, Context &, Renderer& renderer) const;
        void WriteFooter(Atlas const& atlas, Context &, Renderer& renderer) const;
    };
}

