#pragma once

#include <iostream>
#include "ChessClock/Config.hpp"
#include "ChessClock/Logger.hpp"
#include "ChessClock/ThirdParty/nameof.hpp"

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
        static std::shared_ptr<Ty> Load(std::string const& rootFolder, std::string const &name, Args... args)
        {
            LOG_ERROR() << "Not implemented trying to load resource '" << name << "' of type " << NAMEOF_TYPE(Ty) << std::endl;
            return 0;
        }
    };
}
