#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/JsonReader.hpp"
#include "Gambit/Context.hpp"

namespace ChessClock
{
    using namespace Gambit;

    template <class Derived>
    class SceneBase
        : protected JsonReader
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
