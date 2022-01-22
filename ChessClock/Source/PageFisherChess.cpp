#pragma once

#include "ChessClock/PageFisherChess.hpp"

namespace ChessClock
{
    void PageFisherChess::Prepare(Context&) 
    {
    }

    bool PageFisherChess::ProcessEvents(Context& ctx, SDL_Event const&)
    {
        return true;
    }

    void PageFisherChess::Update(Context&)
    {
    }

    void PageFisherChess::Render(Context&) const
    {
    }
}
