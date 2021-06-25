#pragma once

#include "Gambit/Logger.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    class UiCallBacks
    {
        static inline Gambit::Logger _log{ "CallBacks" };

    public:
        typedef std::function<void(ObjectPtr source)> Callback;

    protected:
        typedef std::unordered_map<string, Callback> Callbacks;
        Callbacks _callbacks;

    public:
        bool AddCallback(string const &name, Callback);
        bool RemoveCallback(string const &name);

        void Call(string const& name, ObjectPtr source) const;
    };
}

