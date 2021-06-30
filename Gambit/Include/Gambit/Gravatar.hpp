#pragma once

#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class Gravatar
    {
        typedef std::unordered_map<string, string> EmailToResource;

        int const CacheSizeBytes = 20*1000;

    public:
        Gravatar(const char *jsonFile);

        TexturePtr GetPortrait(const char *email);

        void ClearCache();
    };
}

