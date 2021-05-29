#pragma once

#include "ChessClock/ResourceBase.hpp"

namespace ChessClock
{
    template <class Ty>
    class Resource : public ResourceBase
    {
        typedef Ty ResourceType;

        ResourceType _resource;

    public:
        const Ty& Get() const
        {
            return default(Ty);
        }
    };
}
