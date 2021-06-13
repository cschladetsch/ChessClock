#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ResourceId.hpp"

namespace Gambit
{
    class ResourceBase
        : public std::enable_shared_from_this<ResourceBase> 
    {
        ResourceId _resourceId;

    public:
        Guid GetGuid() const { return _resourceId.GetGuid(); }
        std::string GetName() const { return _resourceId.GetName(); }
        ResourceId const& GetResourceId() const { return _resourceId; }

    public:
        ResourceBase() { }
        ResourceBase(ResourceId resourceId)
            : _resourceId(resourceId) { }

        std::shared_ptr<ResourceBase> SharedBase() { return std::enable_shared_from_this<ResourceBase>::shared_from_this(); }
    };
}

