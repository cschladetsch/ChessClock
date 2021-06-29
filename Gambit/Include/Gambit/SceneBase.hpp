#pragma once

#include "Gambit/Context.hpp"
#include "Gambit/JsonReader.hpp"

namespace ChessClock
{
    template <class Derived>
    class SceneBase
        : protected Gambit::JsonReader
    {
    public:
        typedef typename Derived::Values Values;
        typedef typename Context<Values> Context;

        virtual bool Setup(Context &) = 0;
    //    virtual bool ProcessEvents(Context &) = 0;
    //    virtual bool Present(Context &) = 0;

    //protected:
    //    bool ParseJson(JsonNext &next) = 0;
    };

}
