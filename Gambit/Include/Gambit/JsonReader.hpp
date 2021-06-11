#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Logger.hpp"

namespace Gambit
{
    class JsonReader
    {
        static inline Logger _log{ "JsonReader" };

    public:
        bool Read(const char* fileName);

        virtual bool ReadJson(std::ifstream &) = 0;
    };
}
