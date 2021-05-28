#pragma once

#include <string>

#include "ChessClock/EResourceType.hpp"

namespace ChessClock
{
    class ResourceId
    {
        int _id{ 0 };
        std::string _name;
        bool _exists{ false };
        EResourceType _type;

    public:
        int GetId() const { return _id;  }
        std::string GetName() const { return _name;  }
        EResourceType GetType() const { return _type; }
        bool Exists() const { return _exists; }

        ResourceId() { }
        ResourceId(int id) : _id(id) { }
        ResourceId(std::string name) : _name(name) { }
        ResourceId(int id, std::string name) : _id(id), _name(name) { }
    };
}
