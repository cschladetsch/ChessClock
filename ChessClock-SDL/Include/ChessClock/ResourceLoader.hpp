#pragma once

#include <iostream>

#include "ChessClock/ThirdParty/nameof.hpp"

#include "ChessClock/Config.hpp"
#include "ChessClock/Logger.hpp"
#include "ChessClock/ResourceBase.hpp"

namespace ChessClock
{
    struct ResourceLoaderBase
    {
        static inline Logger _log{ "ResourceLoader" };
    };

    template <class Ty>
    struct ResourceLoader : ResourceLoaderBase
    {
        template <class ...Args>
        static shared_ptr<Ty> Load(string const& fileName, ResourceId const &id, Args... args)
        {
            return Ty::Load(fileName, id, args...);
        }
    };
}
