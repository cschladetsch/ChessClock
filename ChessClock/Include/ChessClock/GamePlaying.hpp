#pragma once

#include "ChessClock/ESide.hpp"
#include "ChessClock/EGameState.hpp"
#include "ChessClock/Player.hpp"
#include "ChessClock/GameBase.hpp"

namespace ChessClock
{
    class GamePlaying 
        : public GameBase
    {
        static inline Logger _log{ "GamePlaying" };

        Gambit::MilliSeconds _gameTime{ 0 };
        Gambit::MilliSeconds _lastGameTime{ 0 };
        TimeControl _timeControl{ 5,0 };

        ObjectPtr _leftFace, _rightFace;
        ObjectPtr _whitePawn, _blackPawn;
        ObjectPtr _pauseButton;

        Player _playerLeft, _playerRight;
        EColor _currentColor{ EColor::White };
        EGameState _gameState{ EGameState::Ready };

        bool _paused{ true };

    public:
        GamePlaying() = default;

        void Prepare(Context &) override;
        void Render(Context &) const override;
        void Update(Context &) override;
        bool ProcessEvents(Context &context, SDL_Event const &) override;

        void SetSprites(ObjectPtr const &left, ObjectPtr const &right, ObjectPtr const &whitePawn, ObjectPtr const &blackPawn, ObjectPtr const &pauseButton);

        void ResetGame();

        void SetGameState(EGameState);
        EGameState GetGameState() const { return _gameState; }

        void SetTimeControl(TimeControl timeControl);
        void SetTimeControl(ESide side, TimeControl timeControl);

        TimeControl GetTimeControl() const { return _timeControl; }

        void Pause(bool paused = true);
        bool IsPaused() const { return _paused; }
        void TogglePause() { Pause(!_paused); }

        void SetColor(ESide side, EColor color);

        Player const &LeftPlayer() const { return _playerLeft; }
        Player const &RightPlayer() const { return _playerRight; }

        Player const& WhitePlayer() const { return _playerLeft.GetColor() == EColor::White ? _playerLeft : _playerRight; }
        Player const& BlackPlayer() const { return _playerLeft.GetColor() == EColor::Black ? _playerLeft : _playerRight; }

        Player const &CurrentPlayer() const { return _currentColor == EColor::White ? WhitePlayer() : BlackPlayer(); }

        EColor GetPlayerTimedOut() const;

        void LeftPressed();
        void RightPressed();

    private:
        void SetupGameSprites(Gambit::ResourceManager &, Gambit::Renderer &, Values &values);

        void SettingsPressed(Context &, ObjectPtr const &source);
        void PausePressed(Context &, ObjectPtr const &source);
        void VolumePressed(Context &, ObjectPtr const &source);

        bool ToggleWhenPaused();
        void ToggleColor();

        void RockerPressed();
        Player &CurrentPlayer() { return _currentColor == EColor::White ? WhitePlayer() : BlackPlayer(); }

        Player &WhitePlayer() { return _playerLeft.GetColor() == EColor::White ? _playerLeft : _playerRight; }
        Player &BlackPlayer() { return _playerLeft.GetColor() == EColor::Black ? _playerLeft : _playerRight; }

        Player& GetPlayer(ESide side);

        void ChangeTurn();
    };
}

