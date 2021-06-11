#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/Json.hpp"
#include "Gambit/Logger.hpp"

namespace Gambit
{
    class JsonReader
    {
        static inline Logger _log{ "JsonReader" };

    protected:
        typedef ::nlohmann::detail::iteration_proxy_value<nlohmann::detail::iter_impl<nlohmann::json>> JsonNext;
        virtual bool ParseJson(JsonNext &next) = 0;

    public:
        bool ReadJson(const char* fileName);
    };
}
