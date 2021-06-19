#pragma once

#include "Gambit/JsonReader.hpp"
#include "Gambit/Context.hpp"

namespace ChessClock
{
    using namespace Gambit;

    class SplashScene
        : JsonReader<SplashScene>
    {
    public:
        struct Values;
        typedef Gambit::Context<Values> Context;

        SplashScene() = default;
        SplashScene(const char *jsonConfig)
            : JsonReader(jsonConfig)
        {
        }

        bool Setup(Context &ctx);
        bool ProcessEvents(Context &);
        bool Present(Context &);

    private:
        bool ParseJson(JsonNext &next);
    };
}

