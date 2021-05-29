#pragma once

#include <string>

#include "crossguid/guid.hpp"

#include "ChessClock/EResourceType.hpp"

namespace ChessClock
{
    typedef xg::Guid Guid;

    class ResourceId
    {
        Guid _id;
        std::string _name;
        bool _exists{ false };
        EResourceType _type{ EResourceType::None };

    public:
        Guid GetGuid() const { return _id; }
        std::string GetName() const { return _name; }
        EResourceType GetType() const { return _type; }
        bool Exists() const { return _exists; }

        ResourceId() { }
        ResourceId(Guid id) : _id(id) { }
        ResourceId(std::string name) : _name(name) { }
        ResourceId(Guid id, std::string name) : _id(id), _name(name) { }

        friend bool operator==(ResourceId const& left, ResourceId const& right)
        {
            return left._id == right._id;
        }
    };
}
