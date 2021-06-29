#include "ChessClock/GameSplash.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/Root.hpp"

namespace ChessClock
{
    void GameSplash::Prepare(Context &context)
    {
    }
       
    void GameSplash::Update(Context &context) 
    {
        if (Gambit::TimeNowSeconds() > 2)
        {
            context.values->Root->Transition(context, EPage::Playing);
        }
    }

    void GameSplash::Render(Context &context) const
    {
        context.values->GetCurrentScene()->Render(context.renderer);
    }

    bool GameSplash::ProcessEvents(Context &ctx, SDL_Event const &)
    {
        return false;
    }
}
