#include "Gambit/TimerFont.hpp"

#include "ChessClock/Root.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/GameSettings.hpp"
#include "ChessClock/TimeControl.hpp"

namespace ChessClock
{
    void GameSettings::Prepare(Context &context)
    {
        AddCallback("PlayPressed", [&context](auto &ctx, auto) { context.MyValues->MyRoot->StartTransitionTo(ctx, EPage::Playing); });
        AddCallback("IncrementMinutesPressed", [this](auto &, auto) { this->MyTimeControl.AddMinutes(1); });
        AddCallback("DecrementMinutesPressed", [this](auto &, auto) { this->MyTimeControl.AddMinutes(-1); });
        AddCallback("IncrementSecondsPressed", [this](auto &, auto) { this->MyTimeControl.AddSeconds(1); });
        AddCallback("DecrementSecondsPressed", [this](auto &, auto) { this->MyTimeControl.AddSeconds(-1); });
        AddCallback("IncrementBonusPressed", [this](auto &, auto) { this->MyTimeControl.AddIncrementSeconds(1); });
        AddCallback("DecrementBonusPressed", [this](auto &, auto) { this->MyTimeControl.AddIncrementSeconds(-1); });
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
        Values const &values = *context.MyValues;
        auto &renderer = context.TheRenderer;

        values.GetCurrentScene()->Render(renderer);

        values.NumberFont->DrawTime(renderer, Vector2{ 82,150 }, static_cast<uint8_t>(MyTimeControl.GetMinutes()), static_cast<uint8_t>(MyTimeControl.GetSeconds()));
        values.NumberFont->DrawSeconds(renderer, Vector2{ 570,150 }, static_cast<uint8_t>(MyTimeControl.GetIncrement()));
    }
}

