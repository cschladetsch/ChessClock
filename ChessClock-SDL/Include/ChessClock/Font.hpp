#pragma once

#include <memory>

#include "ChessClock/ResourceLoader.hpp"
#include "ChessClock/Vector2.hpp"

extern "C" {
    struct _TTF_Font;
}
namespace ChessClock
{
    class Renderer;

    class Font
    {
        std::shared_ptr<_TTF_Font> _font;

    public:
        Font(std::shared_ptr<_TTF_Font> font);

        void DrawText(Renderer &, Vector2 const &startPos, const char *text);
        static std::shared_ptr<Font> Load(std::string const& root, std::string const& name);
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
