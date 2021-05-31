#pragma once

#include <iostream>

#include "Gambit/ThirdParty/nameof.hpp"

#include "Gambit/Config.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/ResourceBase.hpp"

namespace Gambit
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
