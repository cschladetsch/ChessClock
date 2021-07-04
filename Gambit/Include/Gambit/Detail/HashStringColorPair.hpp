#pragma once

#include "Gambit/Color.hpp"

namespace std
{
    template <>
    struct hash<pair<string, Gambit::Color>>
    {
        size_t operator()(const pair<string, Gambit::Color>& pair) const noexcept
        {
            return hash<string>()(pair.first) ^ hash<Gambit::Color>()(pair.second);
        }
    };
}

