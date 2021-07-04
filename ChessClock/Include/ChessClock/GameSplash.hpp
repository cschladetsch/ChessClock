#pragma once

#include "ChessClock/Player.hpp"
#include "ChessClock/GameBase.hpp"

namespace ChessClock
{
    class GameSplash
        : public GameBase
    {
        Gambit::MilliSeconds _displayTime{ 3000 };

    public:
        GameSplash() = default;

        void Prepare(Context &) override;
        void Update(Context &) override;
        void Render(Context &) const override;
        bool ProcessEvents(Context &ctx, SDL_Event const &) override;
    };
}

