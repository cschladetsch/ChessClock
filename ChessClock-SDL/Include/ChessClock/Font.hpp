#pragma once

#include <memory>

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

        static std::shared_ptr<Font> Load(std::string const& root, std::string const& name);

        void SetSize(int ptsize) const;
        void SetDpi(int ptsize, int hdpi, int vdpi) const;
        SDL_Texture *DrawText(Renderer &, const char *text, SDL_Color color) const;
    };

    template <>
    struct ResourceLoader<Font> : ResourceLoaderBase
    {
        static std::shared_ptr<Font> Load(std::string const& root, std::string const& name)
        {
            auto font = Font::Load(root, name);
            if (!font)
            {
                LOG_ERROR() << "Couldn't load font " << name << "\n";
            }
            return font;
        }
    };
}
