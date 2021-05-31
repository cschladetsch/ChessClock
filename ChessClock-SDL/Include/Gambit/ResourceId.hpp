#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/Guid.hpp"
#include "Gambit/EResourceType.hpp"

namespace Gambit
{
    typedef xg::Guid Guid;

    class ResourceId
    {
        Guid _guid;
        string _name;
        bool _exists{ false };
        EResourceType _type{ EResourceType::None };

    public:
        Guid GetGuid() const { return _guid; }
        string GetName() const { return _name; }
        EResourceType GetType() const { return _type; }
        bool Exists() const { return _exists; }

        ResourceId() 
            : _guid(xg::newGuid()) { }
        ResourceId(Guid id) 
            : _guid(id) { }
        ResourceId(Guid id, string name) 
            : _guid(id), _name(name) { }
        ResourceId(Guid id, string name, EResourceType type) 
            : _guid(id), _name(name), _type(type) { }

        friend bool operator==(ResourceId const& left, ResourceId const& right)
        {
            return left._guid == right._guid;
        }
    };
}

namespace std
{
    template <>
    struct hash<Gambit::ResourceId>
    {
        std::size_t operator()(const Gambit::ResourceId& k) const
        {
            auto bytes = k.GetGuid().bytes();
            auto longs = reinterpret_cast<const uint64_t*>(&*bytes.begin());
            return longs[0] ^ longs[1];
        }
    };
}