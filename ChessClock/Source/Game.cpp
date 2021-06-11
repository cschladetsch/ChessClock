#include "ChessClock/Game.hpp"

namespace ChessClock
{
    void UiCallBacks::Call(string const& name) const
    {
        auto call = _callbacks.find(name);
        if (call == _callbacks.end())
        {
            LOG_ERROR() << " no callback for " << name << "\n";
            return;
        }
        call->second();
    }

    Game::Game(Navigation &nav)
        : _navigation(nav)
    {
        RegisterCallbacks();
    }

    void Game::ResetGame()
    {
        SetTimeControl(_timeControl);
        Pause();
    }

    void Game::SetGameState(EGameState state)
    {
        LOG_INFO() << "SetGameState " << LOG_VALUE(state) << "\n";
    }

    void Game::SetTimeControl(TimeControl timeControl)
    {
        if (!_paused)
        {
            Pause();
        }
        ResetGame();
        _playerLeft.SetTimeControl(timeControl);
        _playerRight.SetTimeControl(timeControl);
    }

    void Game::Update()
    {
        if (_paused)
        {
            return;
        }
        TimeUnit currentTicks = SDL_GetTicks();
        _gameTime += (TimeUnit)currentTicks - (TimeUnit)_lastGameTime;
        _lastGameTime = (TimeUnit)currentTicks;
    }

    EColor Game::PlayerTimedOut() const
    {
        if (_playerLeft.TimedOut())
        {
            return _playerLeft.GetColor();
        }

        return _playerRight.TimedOut() ? _playerRight.GetColor() : EColor::None;
    }

    void Game::SetColor(ESide side, EColor color)
    {
        if (side == ESide::Left)
        {
            _playerLeft.SetColor(color);
            _playerRight.SetColor(color == EColor::White ? EColor::Black : EColor::White);
        }
        else 
        {
            _playerRight.SetColor(color);
            _playerLeft.SetColor(color == EColor::White ? EColor::Black : EColor::White);
        }
    }

    Player& Game::WhitePlayer() { return _playerLeft.GetColor() == EColor::White ? _playerLeft : _playerRight; }
    Player& Game::BlackPlayer() { return _playerLeft.GetColor() == EColor::Black ? _playerLeft : _playerRight; }

    Player const& Game::WhitePlayer() const { return _playerLeft.GetColor() == EColor::White ? _playerLeft : _playerRight; }
    Player const& Game::BlackPlayer() const { return _playerLeft.GetColor() == EColor::Black ? _playerLeft : _playerRight; }

    Player &Game::CurrentPlayer() { return _currentColor == EColor::White ? WhitePlayer() : BlackPlayer(); }
    Player const &Game::CurrentPlayer() const { return _currentColor == EColor::White ? WhitePlayer() : BlackPlayer(); }

    void Game::RegisterCallbacks()
    {
        _callbacks["Left"] = [this]() { return this->LeftPressed(); };
        _callbacks["Right"] = [this]() { return this->RightPressed(); };
        _callbacks["Pause"] = [this]() { return this->Pause(); };
        _callbacks["Settings"] = [this]() { return this->Settings(); };
        _callbacks["Sound"] = [this]() { return this->Sound(); };
        _callbacks["Back"] = [this]() { return this->GoBack(); };
    }

    void Game::LeftPressed()
    {
        LOG_INFO() << "Left\n";
        if (_paused)
        {
            return;
        }
        TimeUnit now = TimeNow();
        TimeUnit delta = now - _lastGameTime;
        _lastGameTime = now;
        _playerLeft.UpdateTime(delta);
    }

    void Game::RightPressed()
    {
        LOG_INFO() << "Right\n";
        if (_paused)
        {
            return;
        }
        TimeUnit now = TimeNow();
        TimeUnit delta = now - _lastGameTime;
        _lastGameTime = now;
        _playerRight.UpdateTime(delta);
    }

    void Game::Settings()
    {
        LOG_INFO() << "Settings\n";
    }

    void Game::Pause(bool paused)
    {
        _paused = paused;
        if (!paused)
        {
            _lastGameTime = SDL_GetTicks();
        }
        CurrentPlayer().Pause(paused);

        LOG_INFO() << LOG_VALUE(paused) << LOG_VALUE(_gameTime) << "\n";
    }

    void Game::Sound()
    {
        LOG_INFO() << "Sound\n";
    }

    void Game::GoBack() 
    { 
        _navigation.GoBack();
    }
}
