#include <fstream>

#include "Gambit/JsonReader.hpp"

namespace Gambit
{
    bool JsonReader::Read(const char* fileName)
    {
        std::ifstream inFile(fileName);
        if (!inFile)
        {
            LOG_ERROR() << "Couldn't open " << LOG_VALUE(fileName) << "\n";
            return false;
        }

        return ReadJson(inFile);
    }
}
