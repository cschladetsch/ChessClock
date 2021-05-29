#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    struct Vector2;
    class ResourceManager;
    class ResourceBase;
    class Transform;
    class Component;
    class Texture;
    class Object;

    typedef std::shared_ptr<Texture> TexturePtr;
    typedef std::shared_ptr<Component> ComponentPtr;
    typedef std::shared_ptr<Object> ObjectPtr;
    typedef std::shared_ptr<ResourceBase> ResourceBasePtr;
    typedef std::shared_ptr<Transform> TransformPtr;
}

