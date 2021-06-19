#pragma once

#include <fstream>

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/Json.hpp"
#include "Gambit/Logger.hpp"

namespace Gambit
{
    template <class Ty>
    class JsonReader
    {
        static inline Logger _log{ "JsonReader" };

    protected:
        typedef std::map<string, string (Ty::*)> NameToMember;

        NameToMember _jsonToMember;

    protected:
        JsonReader() = default;

        JsonReader(NameToMember const &names)
            : _jsonToMember(names)
        {
        }

        JsonReader(const char *fileName)
        {
            ReadJsonEx(fileName);
        }

        void ReadJsonEx(const char *fileName)
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

    private:
        bool ReadJson(const char *fileName)
        {
            try
            {
                Json j;
                std::ifstream(fileName) >> j;
                for (auto &item : j.items())
                {
                    if (!ParseJson(item))
                    {
                        LOG_WARN() << "Failed to parse '" << item.key() << '\'\n';
                    }
                }
            }
            catch (std::exception &e)
            {
                LOG_ERROR() << "Error reading json " << LOG_VALUE(fileName) << LOG_VALUE(e.what()) << "\n";
                return false;
            }

            return true;
        }
    };
}
