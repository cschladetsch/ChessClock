#pragma once

#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class GameBase
    {
    public:
        virtual bool DrawSprite(Scene const& scene, Renderer& renderer, Object const& object) = 0;
    };
}
