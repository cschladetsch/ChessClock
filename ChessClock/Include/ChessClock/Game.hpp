#pragma once

#include "Gambit/Config.hpp"
#include "Gambit/Logger.hpp"
#include "ChessClock/UiCallBacks.hpp"
#include "ChessClock/Player.hpp"
#include "ChessClock/Navigation.hpp"

namespace ChessClock
{
    class Game
        : public UiCallBacks
    {
        static inline Logger _log{ "Game " };
        Player _playerLeft, _playerRight;
        bool _paused{ true };
        EColor _currentColor;
        Navigation _navigation;
        uint32_t _pauseTime;

    public:
        Game(Navigation &nav);

        bool IsPaused() const { return _paused;  }
        void LeftPressed();
        void RightPressed();

        Player const &CurrentPlayer() const;
        Player &CurrentPlayer();

        void Settings();
        void Pause(bool pause = true);
        void Sound();

    private:
        void RegisterCallbacks();
        void GoBack();
    };
}
