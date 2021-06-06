#pragma once

#include "Gambit/Color.hpp"

namespace std
{
    template <>
    struct hash<pair<string, Gambit::Color>>
    {
        inline size_t operator()(const pair<string, Gambit::Color>& pair) const
        {
            return hash<string>()(pair.first) ^ hash<Gambit::Color>()(pair.second);
        }
    };
}

