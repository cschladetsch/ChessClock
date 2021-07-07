#pragma once

#include "ChessClock/Player.hpp"
#include "ChessClock/GameBase.hpp"

namespace ChessClock
{
    class PageSplash
        : public GameBase
    {
        Gambit::MilliSeconds _displayTime{ 1000 };

    public:
        PageSplash() = default;

        void Prepare(Context &) override;
        void Update(Context &) override;
        void Render(Context &) const override;
        bool ProcessEvents(Context &ctx, SDL_Event const &) override;
    };
}

