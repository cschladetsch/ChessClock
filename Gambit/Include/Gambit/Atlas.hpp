#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
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
