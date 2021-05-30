#pragma once

#include "ChessClock/ResourceBase.hpp"

namespace ChessClock
{
    template <class Ty>
    class Resource : public ResourceBase
    {
        typedef Ty Type;

        std::shared_ptr<Type> _resource;

    public:
        Resource(std::shared_ptr<Type> resource)
            : _resource(resource)
        {
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
