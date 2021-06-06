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
        _callbacks["PressedLeft"] = [this]() { return this->PressedLeft(); };
        _callbacks["PressedRight"] = [this]() { return this->PressedRight(); };
        _callbacks["PressedPause"] = [this]() { return this->PressedPause(); };
        _callbacks["PressedSettings"] = [this]() { return this->PressedSettings(); };
        _callbacks["PressedSound"] = [this]() { return this->PressedSound(); };
    }

    void Game::PressedLeft()
    {
    }

    void Game::PressedRight()
    {
    }

    void Game::PressedSettings()
    {
    }

    void Game::PressedPause()
    {
    }

    void Game::PressedSetup()
    {
    }

    void Game::PressedSound()
    {
    }
}
