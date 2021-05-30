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
            LOG_ERROR() << "Not implemented trying to load resource '" << name << "' of type " << NAMEOF_TYPE(Ty) << std::endl;
            return 0;
        }
    };
}
