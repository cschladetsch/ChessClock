#pragma once

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    class PageBase
    {
    public:
        int LogVerbosity{ 0 };
        String Name;
        GameBasePtr GameBase;
        Gambit::AtlasPtr Atlas;
        Gambit::ScenePtr Scene;

    protected:
        PageBase(GameBasePtr game, Gambit::ScenePtr scene)
            : GameBase(std::move(game))
            , Scene(std::move(scene))
        { }
    };
}

