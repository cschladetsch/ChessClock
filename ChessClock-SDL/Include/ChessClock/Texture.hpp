#pragma once

#include "ChessClock/ResourceBase.hpp"

namespace ChessClock
{
    class Texture : public ResourceBase
    {
    public:
        Texture(ResourceManager&, ResourceId const&);
    };


}
