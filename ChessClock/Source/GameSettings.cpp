#include "ChessClock/Root.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/GameSettings.hpp"

namespace ChessClock
{
    void GameSettings::Prepare(Context &context)
    {
        AddCallback("PlayPressed", [&](auto &ctx, auto source) {
            context.Values->Root->Transition(ctx, EPage::Playing);
        });
        AddCallback("IncrementMinutesPressed", [&](auto &ctx, auto source) { IncrementMinutesPressed(ctx, source); });
        AddCallback("IncrementSecondsPressed", [&](auto &ctx, auto source) { IncrementSecondsPressed(ctx, source); });
        AddCallback("DecrementMinutesPressed", [&](auto &ctx, auto source) { DecrementMinutesPressed(ctx, source); });
        AddCallback("DecrementSecondsPressed", [&](auto &ctx, auto source) { DecrementSecondsPressed(ctx, source); });
        AddCallback("IncrementBonusPressed", [&](auto &ctx, auto source) { IncrementBonusPressed(ctx, source); });
        AddCallback("DecrementBonusPressed", [&](auto &ctx, auto source) { DecrementBonusPressed(ctx, source); });
    }

    void GameSettings::IncrementMinutesPressed(Context &context, ObjectPtr source)
    {
        LOG_DEBUG() << "Inc minutes pressed\n";
    }

    void GameSettings::IncrementSecondsPressed(Context &context, ObjectPtr source)
    {
        LOG_DEBUG() << "Inc seconds pressed\n";
    }

    void GameSettings::DecrementMinutesPressed(Context &context, ObjectPtr source)
    {
        LOG_DEBUG() << "Dec minutes pressed\n";
    }

    void GameSettings::DecrementSecondsPressed(Context &context, ObjectPtr source)
    {
        LOG_DEBUG() << "Dec seconds pressed\n";
    }

    void GameSettings::IncrementBonusPressed(Context &context, ObjectPtr source)
    {
        LOG_DEBUG() << "Inc bonus seconds pressed\n";
    }

    void GameSettings::DecrementBonusPressed(Context &context, ObjectPtr source)
    {
        LOG_DEBUG() << "Dec bonus seconds pressed\n";
    }

    bool GameSettings::ProcessEvents(Context &ctx, SDL_Event const &)
    {
        return false;
    }

    void GameSettings::Update(Context&)
    {
    }

    void GameSettings::Render(Context &context) const
    {
        context.Values->GetCurrentScene()->Render(context.Renderer);
    }
}
