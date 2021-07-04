#include "ChessClock/GameAbout.hpp"
#include "ChessClock/Values.hpp"

namespace ChessClock
{
    void GameAbout::Prepare(Context &)
    {
    }

    bool GameAbout::ProcessEvents(Context &ctx, SDL_Event const &)
    {
        return true;
    }

    void GameAbout::Update(Context&)
    {
    }

    void GameAbout::Render(Context &context) const
    {
        context.RenderScene();
    }
}

