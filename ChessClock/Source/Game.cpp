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

    Game::Game()
    {
        RegisterCallbacks();
    }

    void Game::RegisterCallbacks()
    {
        _callbacks["Left"] = [this]() { return this->Left(); };
        _callbacks["Right"] = [this]() { return this->Right(); };
        _callbacks["Pause"] = [this]() { return this->Pause(); };
        _callbacks["Settings"] = [this]() { return this->Settings(); };
        _callbacks["Sound"] = [this]() { return this->Sound(); };
    }

    void Game::Left()
    {
        LOG_INFO() << "Left\n";
    }

    void Game::Right()
    {
        LOG_INFO() << "Right\n";
    }

    void Game::Settings()
    {
        LOG_INFO() << "Settings\n";
    }

    void Game::Pause()
    {
        LOG_INFO() << "Pause\n";
    }

    void Game::Sound()
    {
        LOG_INFO() << "Sound\n";
    }
}
