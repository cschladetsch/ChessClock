#pragma once

#include "ChessClock/GameRoot.hpp"

namespace ChessClock
{
    class PageBase
    {
    public:
        int LogVerbosity{ 0 };
        std::string Name;
        GameBasePtr GameBase;
    };

    template <class Behaviour>
    class Page
        : public PageBase
    {
    public:
        SharedPtr<Behaviour> Game;
    };
}

