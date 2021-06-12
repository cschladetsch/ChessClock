#pragma once

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
        Navigation _navigation{ };
        TimeUnit _unpauseTime{ 0 };
        TimeUnit _lastGameTime{ 0 };
        TimeUnit _gameTime{ 0 };
        TimeControl _timeControl{ 5,0 };
        EGameState _gameState{ EGameState::None };

    public:
        Game(Navigation &nav);

        void ResetGame();

        void SetGameState(EGameState);
        EGameState GetGameState() const { return _gameState; }

        void SetTimeControl(TimeControl timeControl);
        TimeControl GetTimeControl() const { return _timeControl; }

        bool IsPaused() const { return _paused;  }

        void Update();

        void LeftPressed();
        void RightPressed();

        void SetColor(ESide side, EColor color);

        Player& WhitePlayer();
        Player& BlackPlayer();

        Player const & WhitePlayer() const;
        Player const & BlackPlayer() const;

        Player &CurrentPlayer();
        Player const &CurrentPlayer() const;

        Player const& LeftPlayer() const { return _playerLeft; }
        Player const& RightPlayer() const { return _playerRight; }

        void ToSettings();
        void Pause(bool pause = true);
        void Sound();

        EColor PlayerTimedOut() const;

    private:
        void RegisterCallbacks();
        void GoBack();
    };
}
