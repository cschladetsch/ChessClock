#pragma once

#include "Gambit/Logger.hpp"

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    class UiCallBacks
    {
        static inline Gambit::Logger _log{ "CallBacks" };

    public:
        typedef std::function<void(Context &, ObjectPtr source)> Callback;

    protected:
        typedef std::unordered_map<string, Callback> Callbacks;
        Callbacks _callbacks;

    public:
        bool AddCallback(string const &name, Callback);
        void Call(Context &, ObjectPtr source) const;
        bool RemoveCallback(string const &name);
    };
}

