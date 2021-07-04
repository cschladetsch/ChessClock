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
        if (auto const now = Gambit::TimeNowMillis(); now > _displayTime)
        {
            context.MyValues->MyRoot->TransitionTo(context, EPage::Playing);
        }
    }

    void GameSplash::Render(Context &context) const
    {
        context.RenderScene();
    }

    bool GameSplash::ProcessEvents(Context &ctx, SDL_Event const &)
    {
        return false;
    }
}

