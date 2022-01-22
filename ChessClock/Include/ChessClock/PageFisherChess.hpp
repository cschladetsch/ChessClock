#pragma once

#include "ChessClock/GameBase.hpp"
#include "ChessClock/Piece.hpp"

namespace ChessClock
{
    typedef std::pair<int, Piece> Designation;

    struct Layout
    {

    };

    class PageFisherChess
        : public GameBase
    {
        PageFisherChess() = default;

        static Layout NewLayout()
        {
            return  Layout();
        }

    protected:

        void Prepare(Context&) override;
        bool ProcessEvents(Context& ctx, SDL_Event const&) override;
        void Update(Context&) override;
        void Render(Context&) const override;
    };
}

