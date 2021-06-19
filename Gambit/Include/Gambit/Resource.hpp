#pragma once

#include "Gambit/ResourceBase.hpp"
#include "Gambit/ResourceLoader.hpp"

namespace Gambit
{
    template <class Ty>
    class Resource
        : public ResourceBase
    {
        typedef Ty Type;

        shared_ptr<Type> _resource;

    public:
        Resource(Type* resource, ResourceId const &id, std::function<void(Ty*)> deleter)
            : _resource(resource, deleter), ResourceBase(id) { }

        bool Exists() const
        {
            return _resource.get();
        }

        Type& Get()
        {
            return *_resource;
        }

        const Type& Get() const
        {
            return *_resource;
        }
    };
}
