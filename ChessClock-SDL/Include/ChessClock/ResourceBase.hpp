#pragma once

#include <string>
#include <unordered_map>

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/ResourceId.hpp"

namespace ChessClock
{

    class MetaData
    {
    };

    class ResourceBase
    {
        ResourceId _id;
        void *data{ 0 };
        ResourceManager *_manager{ 0 };
        MetaData _metaData;

    public:
        Guid GetGuid() const { return _id.GetGuid(); }
        std::string GetName() const { return _id.GetName(); }
        ResourceManager *GetManager() const { return _manager; }

        ResourceBase(int id = 0);
    };
}
