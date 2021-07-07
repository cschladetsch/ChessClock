#pragma once

#include "ChessClock/PageBase.hpp"

namespace ChessClock
{
    template <class Behaviour>
    class Page
        : public PageBase
    {
    public:
        Page(SharedPtr<Behaviour> const &page, Gambit::ScenePtr const &scene)
            : PageBase(page, scene)
            , Game(page) { }

        SharedPtr<Behaviour> Game;
    };
}

