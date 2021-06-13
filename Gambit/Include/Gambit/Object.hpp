#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceBase.hpp"
#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class Object
        : public ResourceBase
    {
        static inline Logger _log{ "Object" };

        ResourceManager* _resourceManager{ 0 };
        ResourceId _resourceId;
        TransformPtr _transform;

    public:
        typedef std::vector<ResourceBasePtr> Resources;

        string Sprite;
        int Layer;
        bool Mirror;

        Object(ResourceId const&, ResourceManager& resourceManager);

        TransformPtr GetTransform() const { return _transform; }
        ResourceId const &GetResourceId() const { return _resourceId; }

        void AddResource(ResourceBasePtr component);

        Resources GetResources() const;
        ResourceBasePtr GetResource(Guid const &guid) const;
    };
}
