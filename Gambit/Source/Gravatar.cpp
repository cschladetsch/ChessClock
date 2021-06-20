#include "Gambit/Gravatar.hpp"

namespace Gambit
{
    // see https://en.gravatar.com/site/implement/images/
    Gravatar::Gravatar(const char *jsonFile)
    {
    }

    TexturePtr Gravatar::GetPortrait(const char *email)
    {
        return 0;
    }

    void Gravatar::ClearCache()
    {
    }
}
