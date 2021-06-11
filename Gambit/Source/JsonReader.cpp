#include <fstream>

#include "Gambit/ThirdParty/Json.hpp"
#include "Gambit/JsonReader.hpp"

namespace Gambit
{
    using nlohmann::json;

    bool JsonReader::ReadJson(const char* fileName)
    {
        std::ifstream inFile(fileName);
        if (!inFile)
        {
            LOG_ERROR() << "Couldn't open " << LOG_VALUE(fileName) << "\n";
            return false;
        }

        json j;
        inFile >> j;
        for (auto &item : j.items())
        {
            try
            {
                Parse(item);
            }
            catch (std::exception& e)
            {
                LOG_ERROR() << "Error reading json " << LOG_VALUE(fileName) << "\n";
                LOG_ERROR() << "Error reading json " << e.what() << "\n";
                return false;
            }
        }

        return true;
    }
}
