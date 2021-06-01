#pragma once

#include "Gambit/Transform.hpp"

namespace Gambit
{
    class Scene
    {
        TransformPtr _root;

    public:
        TransformPtr GetRoot() const { return _root; }
    };
}
