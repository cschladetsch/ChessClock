#include "Gambit/TimerFont.hpp"

#include "ChessClock/Root.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/GameSettings.hpp"
#include "ChessClock/TimeControl.hpp"

namespace ChessClock
{
    void GameSettings::Prepare(Context &context)
    {
        AddCallback("PlayPressed", [&](auto &ctx, auto source) { context.Values->Root->Transition(ctx, EPage::Playing); });
        AddCallback("IncrementMinutesPressed", [&](auto &ctx, auto source) { IncrementMinutesPressed(ctx, source); });
        AddCallback("IncrementSecondsPressed", [&](auto &ctx, auto source) { IncrementSecondsPressed(ctx, source); });
        AddCallback("DecrementMinutesPressed", [&](auto &ctx, auto source) { DecrementMinutesPressed(ctx, source); });
        AddCallback("DecrementSecondsPressed", [&](auto &ctx, auto source) { DecrementSecondsPressed(ctx, source); });
        AddCallback("IncrementBonusPressed", [&](auto &ctx, auto source) { IncrementBonusPressed(ctx, source); });
        AddCallback("DecrementBonusPressed", [&](auto &ctx, auto source) { DecrementBonusPressed(ctx, source); });
    }

    void GameSettings::IncrementMinutesPressed(Context &context, ObjectPtr source)
    {
        TimeControl.AddMinutes(1);
    }

    void GameSettings::IncrementSecondsPressed(Context &context, ObjectPtr source)
    {
        TimeControl.AddSeconds(1);
    }

    void GameSettings::DecrementMinutesPressed(Context &context, ObjectPtr source)
    {
        TimeControl.AddMinutes(-1);
    }

    void GameSettings::DecrementSecondsPressed(Context &context, ObjectPtr source)
    {
        TimeControl.AddSeconds(-1);
    }

    void GameSettings::IncrementBonusPressed(Context &context, ObjectPtr source)
    {
        TimeControl.AddIncrementSeconds(1);
    }

    void GameSettings::DecrementBonusPressed(Context &context, ObjectPtr source)
    {
        TimeControl.AddIncrementSeconds(-1);
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
        Values const &values = *context.Values;
        auto &renderer = context.Renderer;

        values.GetCurrentScene()->Render(renderer);

        values.NumberFont->DrawTime(renderer, Vector2{ 82,150 }, static_cast<uint8_t>(TimeControl.GetMinutes()), static_cast<uint8_t>(TimeControl.GetSeconds()));
        values.NumberFont->DrawSeconds(renderer, Vector2{ 570,150 }, static_cast<uint8_t>(TimeControl.GetIncrement()));
    }
}

