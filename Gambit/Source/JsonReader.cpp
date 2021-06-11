#include <fstream>

#include "Gambit/ThirdParty/Json.hpp"
#include "Gambit/JsonReader.hpp"

namespace Gambit
{
    using ifstream = std::ifstream;
    using exception = std::exception;
    using nlohmann::json;

    bool JsonReader::ReadJson(const char* fileName)
    {
        try
        {
            ifstream inFile(fileName);
            if (!inFile)
            {
                LOG_ERROR() << "Couldn't open " << LOG_VALUE(fileName) << "\n";
                return false;
            }

            json j;
            inFile >> j;
            for (auto& item : j.items())
            {
                ParseJson(item);
            }
        }
        catch (exception& e)
        {
            LOG_ERROR() << "Error reading json " << LOG_VALUE(fileName) << "\n";
            LOG_ERROR() << "Error reading json " << e.what() << "\n";
            return false;
        }

        return true;
    }
}
