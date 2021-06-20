#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/Http.hpp"
#include "Gambit/ThirdParty/Json.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock::Lichess
{
    enum class EFormat
    {
        Blitz,
        Bullet,
        Rapid,
    };

    class Lichess
    {
        Lichess(const char *accessToken);

        int GetRating(const char *name, EFormat format);
        TexturePtr GetPortait(int id);
    };
}

