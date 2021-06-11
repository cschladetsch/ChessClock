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

    Player& Game::CurrentPlayer()
    {
        return _playerLeft;
    }

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
    }

    void Game::RightPressed()
    {
        LOG_INFO() << "Right\n";
    }

    void Game::Settings()
    {
        LOG_INFO() << "Settings\n";
    }

    void Game::Pause(bool paused)
    {
        LOG_INFO() << "Pause\n";
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
