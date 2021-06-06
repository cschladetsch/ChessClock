#pragma once

#include <functional>
#include "ChessClock/Player.hpp"

namespace ChessClock
{
    using string = std::string;

    class UiCallBacks
    {
    public:
        typedef std::function<void()> Callback;

    private:
        typedef std::unordered_map<string, Callback> Callbacks;
        Callbacks _callbacks;

    public:
        void AddCallback(string name, Callback);
        void RemoveCallback(string name);
    };

    class Game
        : public UiCallBacks
    {
        Player playerLeft, playerRight;

    public:
        void PressedLeft();
        void PressedRight();

        void PressedOptions();
        void PressedPause();
        void PressedSetup();
        void PressedSound();

    private:
        void RegisterCallbacks();
    };
}
