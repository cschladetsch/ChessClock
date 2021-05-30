#pragma once

#include <memory>
#include <tuple>

#include "ChessClock/ResourceLoader.hpp"
#include "ChessClock/Vector2.hpp"

extern "C" {
    struct _TTF_Font;
    struct SDL_Texture;
    struct SDL_Color;
}

namespace ChessClock
{
    class Renderer;

    class Font
    {
        _TTF_Font *_font;

    public:
        Font(_TTF_Font *font);

        template <class ...Args>
        static std::shared_ptr<Font> Load(std::string const& root, std::string const& name, Args... args)
        {
            int ptsize = std::get<0>(std::tuple{ args... });
            return LoadFont(root, name, ptsize);
        }

        SDL_Texture *DrawText(Renderer &, const char *text, SDL_Color color) const;

        static std::shared_ptr<Font> LoadFont(std::string const& folder, std::string const& name, int ptsize);
    };

    template <>
    struct ResourceLoader<Font> : ResourceLoaderBase
    {
        template <class ...Args>
        static std::shared_ptr<Font> Load(std::string const& root, std::string const& name, Args... args)
        {
            auto font = Font::Load(root, name, args...);
            if (!font)
            {
                LOG_ERROR() << "Couldn't load font " << name << "\n";
            }
            return font;
        }
    };
}
