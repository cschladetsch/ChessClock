#pragma once

#include "ChessClock/GameBase.hpp"
#include "ChessClock/TimeControl.hpp"

namespace ChessClock
{
    class GameSettings
        : public GameBase
    {
        static inline Logger _log{ "GameSettings" };

    public:
        TimeControl TimeControl;

        GameSettings() = default;

    protected:
        void Prepare(Context&) override;
        bool ProcessEvents(Context& ctx, SDL_Event const&) override;
        void Update(Context&) override;
        void Render(Context&) const override;

    private:
        void IncrementMinutesPressed(Context &context, ObjectPtr source);
        void IncrementSecondsPressed(Context &context, ObjectPtr source);
        void DecrementMinutesPressed(Context &context, ObjectPtr source);
        void DecrementSecondsPressed(Context &context, ObjectPtr source);
        void IncrementBonusPressed(Context &context, ObjectPtr source);
        void DecrementBonusPressed(Context &context, ObjectPtr source);
    };
}

