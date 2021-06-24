#include "Gambit/Object.hpp"
#include "ChessClock/Game.hpp"

namespace ChessClock
{
    Game::Game(Navigation &nav)
        : _navigation(nav)
    {
        RegisterCallbacks();
    }

    void Game::ResetGame()
    {
        SetTimeControl(_timeControl);
        GotoPause();
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
            GotoPause();

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
            _playerLeft.SetColor(color == EColor::White ? EColor::Black : EColor::White);
        }
    }

    void Game::RegisterCallbacks()
    {
        _callbacks["Left"] = [this]() { return this->LeftPressed(); };
        _callbacks["Right"] = [this]() { return this->RightPressed(); };
        _callbacks["Pause"] = [this]() { return this->GotoPause(); };
        _callbacks["Settings"] = [this]() { return this->GotoSettings(); };
        _callbacks["Sound"] = [this]() { return this->GotoSound(); };
        _callbacks["Back"] = [this]() { return this->GoBack(); };
    }

    void Game::LeftPressed()
    {
        //if (_currentColor != CurrentPlayer().GetColor())
            RockerPressed();
    }

    void Game::RightPressed()
    {
        //if (_currentColor != CurrentPlayer().GetColor())
            RockerPressed();
    }

    void Game::RockerPressed()
    {
        if (_paused
            && _gameState == EGameState::Ready
            && _currentColor == EColor::Black)
        {
            _gameState = EGameState::Playing;
            _currentColor = EColor::White;
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

    Player& Game::GetPlayer(ESide side)
    {
        return side == ESide::Left ? _playerLeft : _playerRight;
    }

    void Game::SetFaces(ObjectPtr left, ObjectPtr right) 
    {
        _leftFace = left;  _rightFace = right;
    }

    void Game::ChangeTurn()
    {
        TimeUnit now = TimeNowMillis();
        TimeUnit delta = now - _lastGameTime;
        _lastGameTime = now;
        Player& currentPlayer = CurrentPlayer();
        currentPlayer.AddMillis(-delta);
        currentPlayer.AddSeconds(currentPlayer.GetIncrement());
        _currentColor = _currentColor == EColor::White ? EColor::Black : EColor::White;

        _leftFace->Tint = _rightFace->Tint = "inactive_player";
        if (LeftPlayer().GetColor() == _currentColor)
            _leftFace->Tint = "active_player";
        else
            _rightFace->Tint = "active_player";

        _rightFace->Tint = "active_player";
        _leftFace->Tint = "active_player";
    }

    void Game::GotoPause(bool paused)
    {
        _paused = paused;
        if (!paused)
            _lastGameTime = TimeNowMillis();

        CurrentPlayer().Pause(paused);

        LOG_INFO() << LOG_VALUE(paused) << LOG_VALUE(_gameTime) << "\n";
    }

    void Game::GotoSettings()
    {
        LOG_INFO() << "Goto Settings\n";
        Pause();
    }

    void Game::GotoSound()
    {
        LOG_INFO() << "Goto Sound\n";
        Pause();
    }

    void Game::GoBack() 
    { 
        _navigation.GoBack();
    }
}

