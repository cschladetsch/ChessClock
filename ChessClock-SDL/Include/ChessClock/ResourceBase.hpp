#pragma once

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/ResourceId.hpp"
#include "ChessClock/MetaData.hpp"

namespace ChessClock
{
    class ResourceBase
    {
        ResourceId _resourceId;
        ResourceManager *_manager{ 0 };

    public:
        Guid GetGuid() const { return _resourceId.GetGuid(); }
        std::string GetName() const { return _resourceId.GetName(); }
        ResourceId const& GetResourceId() const { return _resourceId; }
        ResourceManager *GetManager() const { return _manager; }

        ResourceBase() { }
        ResourceBase(ResourceManager& resourceManager, ResourceId resourceId);
    };
}
