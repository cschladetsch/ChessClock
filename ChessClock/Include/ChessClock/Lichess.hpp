#pragma once

#include "Gambit/ForwardReferences.hpp"

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
        explicit Lichess(const char *accessToken);

        int GetRating(const char *name, EFormat format);
        Gambit::TexturePtr GetPortait(int id);
    };
}

