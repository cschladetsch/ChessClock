#pragma once

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    class PageBase
    {
    public:
        int LogVerbosity{ 0 };
        std::string Name;
        Gambit::AtlasPtr Atlas;
        GameBasePtr GameBase;
        Gambit::ScenePtr Scene;

    protected:
        PageBase(GameBasePtr game, Gambit::ScenePtr scene)
            : GameBase(std::move(game))
            , Scene(std::move(scene))
        { }
    };

}

