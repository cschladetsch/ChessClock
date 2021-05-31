#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ResourceId.hpp"
#include "Gambit/MetaData.hpp"

namespace Gambit
{
    class ResourceBase
    {
        ResourceId _resourceId;
        MetaData _metaData;

    public:
        Guid GetGuid() const { return _resourceId.GetGuid(); }
        std::string GetName() const { return _resourceId.GetName(); }
        ResourceId const& GetResourceId() const { return _resourceId; }

        ResourceBase() { }
        ResourceBase(ResourceId resourceId)
            : _resourceId(resourceId)
        {
        }
    };
}
