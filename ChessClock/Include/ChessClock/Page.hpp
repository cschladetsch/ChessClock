#pragma once

#include "Gambit/Scene.hpp"

#include "ChessClock/GameRoot.hpp"

namespace ChessClock
{
    class PageBase
    {
    public:
        int LogVerbosity{ 0 };
        std::string Name;
        //ScenePtr Scene;
        GameBasePtr GameBase;
    };

    template <class Behaviour>
    class Page
        : public PageBase
    {
    public:
        shared_ptr<Behaviour> Game;
    };
}

