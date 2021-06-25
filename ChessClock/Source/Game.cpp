#include "Gambit/Object.hpp"
#include "ChessClock/Game.hpp"
#include "ChessClock/GameRoot.hpp"

namespace ChessClock
{
    Game::Game(Navigation &nav)
        : _navigation(nav)
    {
    }

    void Game::ResetGame()
    {
        SetTimeControl(_timeControl);
        SetColor(ESide::Left, EColor::White);
        Pause();
    }

    void Game::SetGameState(EGameState state)
    {
        LOG_INFO() << "Change state:" << LOG_VALUE(state) << "\n";
    }

    void Game::SwapColors()
    {
        std::swap(_playerLeft, _playerRight);
    }

    void Game::SetTimeControl(TimeControl timeControl)
    {
        if (!_paused)
            Pause();

        _playerLeft.SetTimeControl(timeControl);
        _playerRight.SetTimeControl(timeControl);
    }

    void Game::SetTimeControl(ESide side, TimeControl timeControl)
    {
        GetPlayer(side).SetTimeControl(timeControl);
    }

    void Game::Update()
    {
        if (_paused)
            return;

        TimeUnit now = TimeNowMillis();
        TimeUnit delta = now - _lastGameTime;
        _gameTime += delta;
        _lastGameTime = now;

        CurrentPlayer().AddMillis(-delta);
    }

    EColor Game::GetPlayerTimedOut() const
    {
        if (_playerLeft.HasTimedOut())
            return _playerLeft.GetColor();

        return _playerRight.HasTimedOut() ? _playerRight.GetColor() : EColor::None;
    }

    void Game::SetColor(ESide side, EColor color)
    {
        if (side == ESide::Left)
        {
            _playerLeft.SetColor(color);
            _playerRight.SetColor(OtherColor(color));
        }
        else
        {
            _playerRight.SetColor(color);
            _playerLeft.SetColor(OtherColor(color));
        }
    }

    bool Game::ToggleWhenPaused()
    {
        if (IsPaused() && CurrentPlayer().GetColor() != _currentColor)
        {
            ToggleColor();
            return true;
        }

        return false;
    }

    void Game::LeftPressed()
    {
        if (ToggleWhenPaused())
            return;

        RockerPressed();
    }

    void Game::RightPressed()
    {
        if (ToggleWhenPaused())
            return;

        RockerPressed();
    }

    void Game::RockerPressed()
    {
        if (IsPaused())
        {
            ToggleColor();
            return;
        }

        if (_gameState == EGameState::Ready)
        {
            _gameState = EGameState::Playing;
            _lastGameTime = TimeNowMillis();
            Pause(false);
            return;
        }
        else
        {
            if (_gameState == EGameState::Playing)
                ChangeTurn();
        }
    }

    Player &Game::GetPlayer(ESide side)
    {
        return side == ESide::Left ? _playerLeft : _playerRight;
    }

    void Game::SetSprites(ObjectPtr left, ObjectPtr right, ObjectPtr whitePawn, ObjectPtr blackPawn, ObjectPtr pauseButton)
    {
        _leftFace = left;
        _rightFace = right;
        _whitePawn = whitePawn;
        _blackPawn = blackPawn;
        _pauseButton = pauseButton;
    }

    void Game::ChangeTurn()
    {
        TimeUnit now = TimeNowMillis();
        TimeUnit delta = now - _lastGameTime;
        _lastGameTime = now;
        Player &currentPlayer = CurrentPlayer();
        currentPlayer.AddMillis(-delta);
        currentPlayer.AddSeconds(currentPlayer.GetIncrement());

        ToggleColor();
    }

    void Game::ToggleColor()
    {
        _currentColor = OtherColor(_currentColor);

        _leftFace->Tint = _rightFace->Tint = "inactive_player";
        if (LeftPlayer().GetColor() == _currentColor)
            _leftFace->Tint = "active_player";
        else
            _rightFace->Tint = "active_player";
    }

    void Game::OnPressed(GameRoot *root, GameRoot::Context &context, Vector2 where) const
    {
        root->OnPressed(context, where);
    }

    void Game::Pause(bool paused)
    {
        _paused = paused;
        if (!paused)
            _lastGameTime = TimeNowMillis();

        CurrentPlayer().Pause(paused);

        _pauseButton->Tint = _paused ? "white" : "active_player";
        LOG_INFO() << LOG_VALUE(paused) << LOG_VALUE(_gameTime) << "\n";
    }

    void Game::GoBack() 
    { 
        _navigation.GoBack();
    }
}

