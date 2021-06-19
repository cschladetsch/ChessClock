#pragma once

#include "Gambit/JsonReader.hpp"
#include "Gambit/Context.hpp"

namespace ChessClock
{
    using namespace Gambit;

    class SplashScene
        : JsonReader
    {
    public:
        struct Values;
        typedef Gambit::Context<Values> Context;

        bool Setup(Context &ctx);
        bool ProcessEvents(Context &);
        bool Present(Context &);

    private:
        bool ParseJson(JsonNext &next);
    };
}

