#pragma once

#include "ChessClock/GameRoot.hpp"

namespace ChessClock
{
    enum class EPage
    {
        Splash,
        Playing,
        Settings,
        About
    };

    class PageBase
    {
    public:
        int LogVerbosity{ 0 };
        EPage Page;
        std::string Name;
        Gambit::AtlasPtr Atlas;
        Gambit::ScenePtr Scene;
        GameBasePtr GameBase;

    protected:
        PageBase(EPage page, GameBasePtr game)
            : Page(page)
            , GameBase(game) { }
    };

    template <class Behaviour>
    class Page
        : public PageBase
    {
    public:
        Page(EPage page, SharedPtr<Behaviour> game)
            : PageBase(page, game)
            , Game(game) { }

        SharedPtr<Behaviour> Game;
    };
}

