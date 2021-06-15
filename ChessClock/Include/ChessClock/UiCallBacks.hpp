#pragma once

#include "Gambit/Logger.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
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
}

