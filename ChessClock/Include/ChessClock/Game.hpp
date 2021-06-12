#pragma once

#include "ChessClock/UiCallBacks.hpp"
#include "ChessClock/Player.hpp"
#include "ChessClock/Navigation.hpp"

namespace ChessClock
{
    class Game
        : public UiCallBacks
    {
        static inline Logger _log{ "Game" };

        Player _playerLeft, _playerRight;
        bool _paused{ true };
        Navigation _navigation{ };
        MilliSeconds _lastGameTime{ 0 };
        MilliSeconds _gameTime{ 0 };
        TimeControl _timeControl{ 5,0 };
        EGameState _gameState{ EGameState::None };
        EColor _currentColor{ EColor::White };

    public:
        Game(Navigation &nav);

        void ResetGame();

        void SetGameState(EGameState);
        EGameState GetGameState() const { return _gameState; }

        void SetTimeControl(TimeControl timeControl);
        void SetTimeControl(ESide side, TimeControl timeControl);

        TimeControl GetTimeControl() const { return _timeControl; }
        TimeControl GetTimeControl(ESide side) const;

        bool IsPaused() const { return _paused;  }

        void Update();

        void LeftPressed();
        void RightPressed();

        void SetColor(ESide side, EColor color);

        Player const &LeftPlayer() const { return _playerLeft; }
        Player const &RightPlayer() const { return _playerRight; }

        Player const& WhitePlayer() const { return _playerLeft.GetColor() == EColor::White ? _playerLeft : _playerRight; }
        Player const& BlackPlayer() const { return _playerLeft.GetColor() == EColor::Black ? _playerLeft : _playerRight; }

        Player const &CurrentPlayer() const { return _currentColor == EColor::White ? WhitePlayer() : BlackPlayer(); }

        void GotoSettings();
        void GotoPause(bool pause = true);
        void GotoSound();

        EColor PlayerTimedOut() const;

    private:
        Player &CurrentPlayer() { return _currentColor == EColor::White ? WhitePlayer() : BlackPlayer(); }

        Player &WhitePlayer() { return _playerLeft.GetColor() == EColor::White ? _playerLeft : _playerRight; }
        Player &BlackPlayer() { return _playerLeft.GetColor() == EColor::Black ? _playerLeft : _playerRight; }

        void RegisterCallbacks();
        void GoBack();

        void ChangeTurn();
    };
}
