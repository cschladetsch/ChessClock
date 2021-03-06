#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/ThirdParty/Guid.hpp"

namespace Gambit
{
    typedef xg::Guid Guid;

    class ResourceId
    {
        Guid _guid;
        string _name;

    public:
        const Guid &GetGuid() const { return _guid; }
        const string &GetName() const { return _name; }

        ResourceId() 
            : _guid(xg::newGuid()) { }

        explicit ResourceId(Guid const &id) 
            : _guid(id) { }

        explicit ResourceId(string const &name)
            : _guid(xg::newGuid()), _name(name) { }

        ResourceId(Guid const &id, string const &name) 
            : _guid(id), _name(name) { }

        friend bool operator==(ResourceId const& left, ResourceId const& right)
        {
            return left._guid == right._guid;
        }
    };

    inline std::ostream& operator<<(std::ostream& out, Gambit::ResourceId const& id)
    {
        return out << "[" << LOG_VALUE(id.GetGuid()) << LOG_VALUE(id.GetName()) << "]";
    }

}

namespace std
{
    template <>
    struct hash<Gambit::ResourceId>
    {
        std::size_t operator()(const Gambit::ResourceId& rid) const noexcept
        {
            auto bytes = rid.GetGuid().bytes();
            const auto longs = reinterpret_cast<const uint64_t*>(&*bytes.begin());
            return longs[0] ^ longs[1];
        }
    };
}

