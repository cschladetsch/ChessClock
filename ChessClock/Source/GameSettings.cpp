#include "ChessClock/GameSettings.hpp"

#include "ChessClock/Root.hpp"
#include "ChessClock/Values.hpp"

namespace ChessClock
{
    void GameSettings::Prepare(Context &context)
    {
        AddCallback("PlayPressed", [this, &context](auto &ctx, auto source) { context.values->Root->Transition(ctx, EPage::Playing); });
        //AddCallback("PausePressed", [this, &context](auto &ctx, auto source) { PausePressed(ctx, source); });
        //AddCallback("VolumePressed", [this, &context](auto &ctx, auto source) { VolumePressed(ctx, source); });
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
        context.values->GetCurrentScene()->Render(context.renderer);
    }
}
