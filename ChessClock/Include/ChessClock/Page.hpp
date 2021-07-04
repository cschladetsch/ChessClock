#pragma once

#include "ChessClock/PageBase.hpp"

namespace ChessClock
{
    template <class Behaviour>
    class Page
        : public PageBase
    {
    public:
        Page(SharedPtr<Behaviour> const &game, Gambit::ScenePtr const &scene)
            : PageBase(game, scene)
            , Game(game) { }

        SharedPtr<Behaviour> Game;
    };
}

