#pragma once

#include "ChessClock/GameBase.hpp"
#include "ChessClock/TimeControl.hpp"

namespace ChessClock
{
    class GameSettings
        : public GameBase
    {
        static inline Logger _log{ "PageSettings" };

    public:
        TimeControl MyTimeControl { 10, 0, 3 };

        GameSettings() = default;

    protected:
        void Prepare(Context&) override;
        bool ProcessEvents(Context& ctx, SDL_Event const&) override;
        void Update(Context&) override;
        void Render(Context&) const override;
    };
}

