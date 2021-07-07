#include "ChessClock/PageAbout.hpp"
#include "ChessClock/Values.hpp"

namespace ChessClock
{
    void PageAbout::Prepare(Context &)
    {
    }

    bool PageAbout::ProcessEvents(Context &ctx, SDL_Event const &)
    {
        return true;
    }

    void PageAbout::Update(Context&)
    {
    }

    void PageAbout::Render(Context &context) const
    {
        context.RenderScene();
    }
}

