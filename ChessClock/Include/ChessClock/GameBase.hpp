#pragma once

#include "Gambit/Context.hpp"

#include "ChessClock/UiCallBacks.hpp"

namespace ChessClock
{
    class Root;

    class GameBase
        : public std::enable_shared_from_this<GameBase>
        , protected UiCallBacks
        , Gambit::NonCopyable
    {
    public:
        GameBase() = default;
        virtual ~GameBase() = default;
        typedef Gambit::Context<Values> Context;

    protected:
        friend class Root;

        void OnPressed(Context &, Vector2 where) const;

        virtual void Prepare(Context &) = 0;
        virtual bool ProcessEvents(Context &ctx, SDL_Event const &) = 0;
        virtual void Update(Context &) = 0;
        virtual void Render(Context &) const = 0;
    };
}

