#pragma once

#include "ChessClock/Player.hpp"
#include "ChessClock/GameBase.hpp"

namespace ChessClock
{
    class GameSplash
        : public GameBase
    {
        Gambit::Seconds _displayTime{ 2 };

    public:
        GameSplash();

        void Prepare(Context &) override;
        void Update(Context &) override;
        void Render(Context &) const override;
        bool ProcessEvents(Context &ctx, SDL_Event const &) override;
    };
}
