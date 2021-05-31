#pragma once

#include <vector>

#include "ChessClock/Logger.hpp"
#include "ChessClock/ResourceId.hpp"
#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    class Object
    {
        ResourceManager* _resourceManager{ 0 };
        ResourceId _resourceId;
        Logger _log{ "Object" };
        TransformPtr _transform;
       
    public:
        typedef std::vector<ComponentPtr> Components;

        Object(ResourceId const &resourceId);

        TransformPtr GetTransform() const { return _transform; }

        void AddComponent(ComponentPtr component);

        Components const& GetComponents() const;
        Component const& GetComponent(Guid const &guid) const;
    };
}
