#pragma once

#include "Gambit/ResourceBase.hpp"

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
            : ResourceBase(id), _resource(resource, deleter)  { }

        bool Exists() const { return _resource.get(); }
        Type& Get() { return *_resource; }
        const Type& Get() const { return *_resource; }
    };
}

