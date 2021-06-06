#pragma once

#include "Gambit/Logger.hpp"
#include "ChessClock/Player.hpp"

namespace ChessClock
{
    using string = std::string;

    class UiCallBacks
    {
        static inline Gambit::Logger _log{ "CallBacks" };
    public:
        typedef std::function<void()> Callback;

    protected:
        typedef std::unordered_map<string, Callback> Callbacks;
        Callbacks _callbacks;

    public:
        void AddCallback(string name, Callback);
        void RemoveCallback(string name);

        void Call(string const& name) const;
    };

    class Game
        : public UiCallBacks
    {
        Player playerLeft, playerRight;

    public:
        Game();

        void PressedLeft();
        void PressedRight();

        void PressedSettings();
        void PressedPause();
        void PressedSetup();
        void PressedSound();

    private:
        void RegisterCallbacks();
    };
}
