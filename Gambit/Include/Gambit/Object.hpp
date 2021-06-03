#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceId.hpp"
#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class Object
    {
        static inline Logger _log{ "Object" };

        ResourceManager* _resourceManager{ 0 };
        ResourceId _resourceId;
        TransformPtr _transform;

    public:
        typedef std::vector<ResourceBasePtr> Resources;

        Object(ResourceManager &rm, ResourceId const &resourceId);

        TransformPtr GetTransform() const { return _transform; }
        ResourceId const &GetResourceId() const { return _resourceId; }

        void AddResource(ResourceBasePtr component);

        Resources GetResources() const;
        ResourceBasePtr GetResource(Guid const &guid) const;
    };
}
