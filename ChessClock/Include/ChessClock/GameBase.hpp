#pragma once

#include "Gambit/Context.hpp"

#include "ChessClock/UiCallBacks.hpp"

namespace ChessClock
{
    class GameRoot;

    class GameBase
        : public std::enable_shared_from_this<GameBase>
        , UiCallBacks
        , Gambit::NonCopyable
    {
    public:
        typedef Gambit::Context<Values> Context;

    protected:
        friend class GameRoot;

        void OnPressed(Context &, Vector2 where) const;

        virtual void Update(Context &) = 0;
        virtual void Render(Context &) const = 0;
        virtual bool ProcessEvents(Context &ctx, SDL_Event const &) = 0;
    };
}

