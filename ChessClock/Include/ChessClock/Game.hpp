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
        static inline Logger _log{ "Game " };
        Player playerLeft, playerRight;

    public:
        Game();

        void Left();
        void Right();

        void Settings();
        void Pause();
        void Sound();

    private:
        void RegisterCallbacks();
    };
}
