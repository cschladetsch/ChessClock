#pragma once

#include "Gambit/Font.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Color.hpp"

namespace Gambit
{
    class NumberFont
        : public std::enable_shared_from_this<NumberFont> 
        , ResourceBase
    {
        typedef std::array<TexturePtr, 10> Digits;

        Digits _digits;
        Rect _rectDigit;
        FontPtr _font;

    public:
        NumberFont(ResourceId const& id, FontPtr font);

        void DrawDigits(Renderer&, Rect const& destRect, char number) const;
        void MakeDigitsTextures(ResourceManager &, Renderer &, Color);
    };
}
