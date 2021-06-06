#pragma once

#include "Gambit/Font.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Color.hpp"

namespace Gambit
{
    class NumberFont
        : public ResourceBase
    {
        typedef std::array<TexturePtr, 10> Digits;
        static inline Logger _log{ "NumberFont" };

        Digits _digits;
        Rect _rectDigit;
        FontPtr _font;

    public:
        NumberFont(ResourceId const& id, FontPtr font);

        void MakeDigitsTextures(ResourceManager &, Renderer &, Color);

        void DrawDigits(Renderer&, Vector2 const& topLeft, char number) const;
        void DrawDigits(Renderer&, Rect const& destRect, char number) const;
    };
}
