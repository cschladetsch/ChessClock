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
        Rect _rectColon;
        FontPtr _font;
        TexturePtr _colon;

    public:
        NumberFont(ResourceId const& id, FontPtr font);

        void MakeTextures(ResourceManager &, Renderer &, Color);

        void DrawTime(Renderer &, Vector2 topLeft, uint8_t minutes, uint8_t seconds) const;
        void DrawTime(Renderer &, Vector2 topLeft, uint8_t minutes, uint8_t seconds, uint8_t millis) const;

    private:
        void DrawDigitPair(Renderer &, Vector2 const &topLeft, uint8_t number) const;
        void DrawColon(Renderer &, Vector2 const &topLeft) const;
    };
}
