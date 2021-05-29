#pragma once

#include "ChessClock/ResourceBase.hpp"

namespace ChessClock
{
    template <class Ty>
    class Resource : public ResourceBase
    {
        typedef Ty Type;

        Type _resource;

    public:
        const Type& Get() const
        {
            return default(Ty);
        }
    };
}
