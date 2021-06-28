#pragma once

#include <fstream>

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/Json.hpp"
#include "Gambit/Logger.hpp"

namespace Gambit
{
    template <class Class>
    class JsonReader
    {
        static inline Logger _log{ "JsonReader" };

    protected:
        typedef std::map<string, string (Class::*)> NameToMember;

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

        template <class Ty, class Klass = Class>
        static bool SetValue(nlohmann::json& item, const string &name, Klass &object, Ty (Klass::* member)
            , std::function<Ty(nlohmann::json &j)> convert = [](nlohmann::json &j) { return j; })
        {
            if (!item.contains(name))
                return false;

            (object.*member) = convert(item[name]);
            return true;
        }

    private:
        bool ReadJson(const char *fileName)
        {
            try
            {
                Json json;
                std::ifstream(fileName) >> json;
                for (auto &item : json.items())
                {
                    if (!ParseJson(item))
                    {
                        LOG_WARN() << "Failed to parse json key '" << item.key() << "'\n";
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
