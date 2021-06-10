#pragma once

#include "Gambit/Config.hpp"
#include "Gambit/Logger.hpp"
#include "ChessClock/UiCallBacks.hpp"
#include "ChessClock/Player.hpp"

namespace ChessClock
{
    class Game
        : public UiCallBacks
    {
        static inline Logger _log{ "Game " };
        Player playerLeft, playerRight;

    public:
        Game();

        void Left();
        void Right();

        void Settings();
        void Pause();
        void Sound();

    private:
        void RegisterCallbacks();
    };
}
