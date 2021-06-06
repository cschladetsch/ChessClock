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

        Digits _digits;
        Rect _rectDigit;
        Rect _rectColon;
        FontPtr _font;
        TexturePtr _colon;

    public:
        TimerFont(ResourceId const& id, FontPtr font);

        void MakeTextures(ResourceManager &, Renderer &, Color);

        Vector2 DrawTime(Renderer &, Vector2 topLeft, uint8_t minutes, uint8_t seconds) const;
        Vector2 DrawTime(Renderer &, Vector2 topLeft, uint8_t minutes, uint8_t seconds, uint8_t millis) const;

    private:
        Vector2 DrawDigitPair(Renderer &, Vector2 const &topLeft, uint8_t number) const;
        Vector2 DrawColon(Renderer &, Vector2 const &topLeft) const;
    };
}
