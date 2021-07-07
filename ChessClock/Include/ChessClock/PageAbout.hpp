#pragma once

#include "ChessClock/GameBase.hpp"

namespace ChessClock
{
    class PageAbout
        : public GameBase
    {
    protected:
        void Prepare(Context&) override;
        bool ProcessEvents(Context& ctx, SDL_Event const&) override;
        void Update(Context&) override;
        void Render(Context&) const override;
    };
}

