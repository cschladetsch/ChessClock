#pragma once

#include <memory>
#include <tuple>

#include "ChessClock/Resource.hpp"
#include "ChessClock/Vector2.hpp"

namespace ChessClock
{
    class Font : public Resource<_TTF_Font>
    {
    public:
        Font(ResourceId const &id, _TTF_Font* font)
            : Resource<_TTF_Font>(font, id, Deleter)
        {
        }

        static void Deleter(_TTF_Font* font);

        template <class ...Args>
        static shared_ptr<Font> Load(std::string const &fileName, ResourceId const &id, Args... args)
        {
            int pointSize = std::get<0>(std::tuple{ args... });
            return LoadFont(fileName, id, pointSize);
        }
        static std::shared_ptr<Font> LoadFont(std::string const& fileName, ResourceId const &id, int pointSize);

        shared_ptr<Texture> DrawText(ResourceManager &, Renderer &, const char *text, SDL_Color color) const;
    };

    template <>
    struct ResourceLoader<Font> : ResourceLoaderBase
    {
        template <class ...Args>
        static std::shared_ptr<Font> Load(std::string const& fileName, ResourceId const &id, Args... args)
        {
            return Font::Load(fileName, id, args...);
        }
    };
}
