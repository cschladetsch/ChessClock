#pragma once

#include "Gambit/Context.hpp"

namespace ChessClock
{
    template <class Values>
    class SceneBase
    {
        typedef Gambit::Context<Values> Ctx;

    protected:
        void AddStep(Ctx&, bool (SceneBase<Values>::*method)(Ctx&))
        {
            ctx.steps.push_back([this, method](auto& ctx) { return (this->*method)(ctx); });
        }
    };
}
