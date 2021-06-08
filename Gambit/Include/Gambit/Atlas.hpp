#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceManager.hpp"
#include "ChessClock/Config.hpp"

namespace ChessClock
{
    class Atlas
    {
        static inline Logger _log{ "Atlas" };
        TexturePtr _texture;

    public:
        Atlas(ResourceManager &);

        bool Load(const char* fileName);
    };
}
