#pragma once

#include "ChessClock/Player.hpp"
#include "ChessClock/Navigation.hpp"
#include "ChessClock/UiCallBacks.hpp"

namespace ChessClock
{
    class Game
        : public UiCallBacks
    {
        static inline Logger _log{ "Game" };

        bool _paused{ true };
        Navigation _navigation{ };
        MilliSeconds _gameTime{ 0 };
        MilliSeconds _lastGameTime{ 0 };
        TimeControl _timeControl{ 5,0 };
        Player _playerLeft, _playerRight;
        EColor _currentColor{ EColor::White };
        EGameState _gameState{ EGameState::None };

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

        void SwapColors();

        EColor GetPlayerTimedOut() const;

    private:
        Player &CurrentPlayer() { return _currentColor == EColor::White ? WhitePlayer() : BlackPlayer(); }

        Player &WhitePlayer() { return _playerLeft.GetColor() == EColor::White ? _playerLeft : _playerRight; }
        Player &BlackPlayer() { return _playerLeft.GetColor() == EColor::Black ? _playerLeft : _playerRight; }

        Player& GetPlayer(ESide side);

        void RegisterCallbacks();
        void GoBack();

        void ChangeTurn();
    };
}
