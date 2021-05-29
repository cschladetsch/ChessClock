#pragma once

#include <memory>
#include "ChessClock/Config.hpp"

namespace ChessClock
{
    struct Vector2;
    class ResourceManager;
    class ResourceBase;
    class Transform;

    typedef std::shared_ptr<ResourceBase> ResourceBasePtr;
    typedef std::shared_ptr<Transform> TransformPtr;
}

