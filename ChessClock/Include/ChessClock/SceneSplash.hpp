#pragma once

#include "Gambit/JsonReader.hpp"
#include "Gambit/Context.hpp"

namespace ChessClock
{
    class SplashScene
        : Gambit::JsonReader<SplashScene>
    {
    public:
        struct Values;
        typedef Gambit::Context<Values> Context;

        SplashScene() = default;

        explicit SplashScene(const char *jsonConfig)
            : JsonReader(jsonConfig)
        { }

        static bool Setup(Context &ctx);
    };
}

