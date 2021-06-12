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
        LOG_INFO() << "SetGameState " << LOG_VALUE(state) << "\n";
    }

    void Game::SetTimeControl(TimeControl timeControl)
    {
        if (!_paused)
        {
            GotoPause();
        }
        _playerLeft.SetTimeControl(timeControl);
        _playerRight.SetTimeControl(timeControl);
    }

    void Game::Update()
    {
        if (_paused)
        {
            return;
        }
        TimeUnit now = TimeNow();
        TimeUnit delta = now - _lastGameTime;
        _gameTime += delta;
        _lastGameTime = now;

        CurrentPlayer().AddMillis(-delta);
    }

    EColor Game::PlayerTimedOut() const
    {
        if (_playerLeft.HasTimedOut())
        {
            return _playerLeft.GetColor();
        }

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
        if (_paused || &CurrentPlayer() == &RightPlayer())
            return;
        ChangeTurn();
    }

    void Game::RightPressed()
    {
        if (_paused || &CurrentPlayer() == &LeftPlayer())
            return;
        ChangeTurn();
    }

    void Game::ChangeTurn()
    {
        TimeUnit now = TimeNow();
        TimeUnit delta = now - _lastGameTime;
        _lastGameTime = now;
        CurrentPlayer().AddMillis(-delta);
        _currentColor = _currentColor == EColor::White ? EColor::Black : EColor::White;
    }

    void Game::GotoPause(bool paused)
    {
        _paused = paused;
        if (!paused)
        {
            _lastGameTime = TimeNow();
        }
        CurrentPlayer().Pause(paused);

        LOG_INFO() << LOG_VALUE(paused) << LOG_VALUE(_gameTime) << "\n";
    }

    void Game::GotoSettings()
    {
        LOG_WARN() << "Goto Settings\n";
    }

    void Game::GotoSound()
    {
        LOG_WARN() << "Goto Sound\n";
    }

    void Game::GoBack() 
    { 
        _navigation.GoBack();
    }
}
