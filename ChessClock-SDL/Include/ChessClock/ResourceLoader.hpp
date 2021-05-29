#pragma once

#include <iostream>
#include "ChessClock/Config.hpp"
#include "ChessClock/ThirdParty/nameof.hpp"

#define STRCAT(A, B) A ## B

namespace ChessClock
{
    template <class Ty>
    struct ResourceLoader
    {
        static inline Logger _log{ "ResourceLoader" };

        static std::shared_ptr<Ty> Load(std::string const& rootFolder, std::string const &name)
        {
            LOG_ERROR() << "Not implemented trying to load resource '" << name << "' of type " << NAMEOF_TYPE(Ty) << std::endl;
            return 0;
        }
    };
}
