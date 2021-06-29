#include "ChessClock/GameSplash.hpp"
#include "ChessClock/Values.hpp"

namespace ChessClock
{
    GameSplash::GameSplash()
    {
    }

    void GameSplash::Prepare(Context &context)
    {
    }
       
    void GameSplash::Update(Context &context) 
    {
        if (Gambit::TimeNowSeconds() > 2)
        {
            //context.Switch(context.values->playing);
        }
    }

    void GameSplash::Render(Context &context) const
    {
        context.values->sceneSplash->Render(context.renderer);
    }

    bool GameSplash::ProcessEvents(Context &ctx, SDL_Event const &)
    {
        return false;
    }
}
