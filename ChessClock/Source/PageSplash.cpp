#include "ChessClock/PageSplash.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/Root.hpp"

namespace ChessClock
{
    void PageSplash::Prepare(Context &context)
    {
    }
       
    void PageSplash::Update(Context &context) 
    {
        if (auto const now = Gambit::TimeNowMillis(); now > _displayTime)
        {
            context.MyValues->MyRoot->StartTransitionTo(context, EPage::Playing);
        }
    }

    void PageSplash::Render(Context &context) const
    {
        context.RenderScene();
    }

    bool PageSplash::ProcessEvents(Context &ctx, SDL_Event const &)
    {
        return false;
    }
}

