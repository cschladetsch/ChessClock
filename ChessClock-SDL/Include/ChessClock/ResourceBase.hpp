#pragma once

#include <string>
#include <unordered_map>

#include "ChessClock/ResourceId.hpp"

namespace ChessClock
{
    class ResourceManager;

    class ResourceBase
    {
        ResourceId _id;
        void* data{ 0 };
        ResourceManager* _manager{ 0 };
        std::unordered_map<std::string, std::string> _metaData;

    public:
        int GetId() const { return _id.GetId(); }
        std::string GetName() const { return _id.GetName(); }
        ResourceManager* GetManager() const { return _manager; }

        ResourceBase(int id = 0);
    };
}
