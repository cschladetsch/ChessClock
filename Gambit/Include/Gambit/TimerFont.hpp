#pragma once

#include "Gambit/Font.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Color.hpp"

namespace Gambit
{
    class TimerFont
        : public ResourceBase
    {
        typedef std::array<TexturePtr, 10> Digits;
        static inline Logger _log{ "NumberFont" };

        FontPtr _font;
        Digits _digits;
        Digits _darkDigits;
        TexturePtr _colon;
        TexturePtr _darkColon;
        Rect _rectDigit;
        Rect _rectColon;

    public:
        Vector2 DarkOffset;

        TimerFont(ResourceId const& id, FontPtr font);

        void MakeTextures(ResourceManager &, Renderer &, Color);

        void DrawTime(Renderer &, Vector2 topLeft, uint8_t minutes, uint8_t seconds) const;

    private:
        void DrawTime(Renderer& renderer, Digits const& digits, TexturePtr colon, Vector2 topLeft, uint8_t minutes, uint8_t seconds) const;
        Vector2 DrawDigitPair(Renderer &, Digits const &, Vector2 const &topLeft, uint8_t number) const;
        Vector2 DrawColon(Renderer&, TexturePtr colon, Vector2 const& topLeft) const;
    };
}
