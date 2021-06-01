#pragma once

#include <vector>

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceId.hpp"
#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class Object
        : std::enable_shared_from_this<Object>
    {
        static inline Logger _log{ "Object" };

        ResourceManager* _resourceManager{ 0 };
        ResourceId _resourceId;
        TransformPtr _transform;

    public:
        typedef std::vector<ComponentPtr> Components;

        Object(ResourceManager &rm, ResourceId const &resourceId);

        TransformPtr GetTransform() const { return _transform; }
        ResourceId const &GetResourceId() const { return _resourceId; }

        void AddComponent(ComponentPtr component);

        Components const& GetComponents() const;
        Component const& GetComponent(Guid const &guid) const;
    };
}
