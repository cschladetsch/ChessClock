#pragma once

#include "Gambit/Resource.hpp"
#include "Gambit/Vector2.hpp"

namespace Gambit
{
    class Font
        : public Resource<_TTF_Font>
    {
        static inline Logger _log{ "Font" };

    public:
        Font(ResourceId const &id, _TTF_Font *font)
            : Resource<_TTF_Font>(font, id, Deleter)
        {
        }

        static void Deleter(_TTF_Font *font);

        template <class ...Args>
        static FontPtr Load(std::string const &fileName, ResourceId const &id, Args... args)
        {
            int pointSize = std::get<0>(std::tuple{ args... });
            return LoadFont(fileName, id, pointSize);
        }

        static FontPtr LoadFont(std::string const& fileName, ResourceId const &id, int pointSize);

        TexturePtr DrawText(ResourceManager &, Renderer &, const char *text, SDL_Color color) const;
    };
}
