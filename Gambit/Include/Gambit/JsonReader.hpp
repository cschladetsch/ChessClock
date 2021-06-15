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
        JsonReader() = default;
        JsonReader(const char *fileName)
        {
            if (!ReadJson(fileName))
            {
                LOG_ERROR() << "Failed to read json '" << LOG_VALUE(fileName) << "' \n";
            }
        }

        typedef ::nlohmann::detail::iteration_proxy_value<nlohmann::detail::iter_impl<nlohmann::json>> JsonNext;
        virtual bool ParseJson(JsonNext &next) = 0;

        template <class Ty, class Cl>
        bool SetValue(JsonNext const &item, string const &name, Cl *instance, Ty(Cl:: *member), std::function<Ty(nlohmann::json &j)> convert = nullptr)
        {
            if (item.key() != name)
                return false;

            if (convert)
                (instance->*member) = convert(item.value());
            else
                (instance->*member) = item.value();
            return true;
        }

    public:
        bool ReadJson(const char* fileName);
    };
}
