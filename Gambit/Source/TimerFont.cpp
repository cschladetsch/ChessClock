#include "Gambit/TimerFont.hpp"
#include "Gambit/Color.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/ThirdParty/SDL.hpp"

namespace Gambit
{
    TimerFont::TimerFont(ResourceId const& id, FontPtr font)
        : ResourceBase(id), _font(std::move(font)), DarkOffset(7,7)
    {
    }

    void TimerFont::DrawTime(Renderer& renderer, Vector2 const &topLeft, uint8_t minutes, uint8_t seconds) const
    {
        DrawTime(renderer, _darkDigits, _darkColon, topLeft + DarkOffset, minutes, seconds);
        DrawTime(renderer, _digits, _colon, topLeft, minutes, seconds);
    }

    void TimerFont::DrawSeconds(Renderer &renderer, Vector2 const &topLeft, uint8_t seconds) const
    {
        DrawSeconds(renderer, _darkDigits, topLeft + DarkOffset, seconds);
        DrawSeconds(renderer, _digits, topLeft, seconds);
    }

    void TimerFont::DrawTime(Renderer& renderer, Digits const& digits, TexturePtr const &colon,  Vector2 const &topLeft, uint8_t minutes, uint8_t seconds) const
    {
        auto tl = topLeft;
        DrawDigitPair(renderer, digits, tl, minutes);
        tl.x += _rectDigit.width * 2;
        DrawColon(renderer, colon, tl);
        tl.x += _rectColon.width;
        DrawDigitPair(renderer, digits, tl, seconds);
    }

    void TimerFont::DrawSeconds(Renderer& renderer, Digits const& digits, Vector2 const &topLeft, uint8_t seconds) const
    {
        DrawDigitPair(renderer, digits, topLeft, seconds);
    }

    void TimerFont::DrawColon(Renderer &renderer, TexturePtr colon, Vector2 const& topLeft) const
    {
        Rect rect{ topLeft.x, topLeft.y - 10, _rectColon.width, _rectColon.height };
        renderer.WriteTexture(colon, nullptr, &rect);
    }

    void TimerFont::DrawDigitPair(Renderer &renderer, Digits const &digits, Vector2 const& topleft, uint8_t number) const
    {
        if (number > 99)
        {
            LOG_ERROR() << "attempt to two-digit draw number with " << LOG_VALUE(number) << "\n";
            return;
        }

        number %= 100;

        Rect firstDigit{ topleft.x, topleft.y, _rectDigit.width, _rectDigit.height };
        Rect secondDigit{ topleft.x + _rectDigit.width, topleft.y, _rectDigit.width, _rectDigit.height };

        const auto digit0 = number / 10;
        const auto digit1 = number % 10;

        renderer.WriteTexture(digits[digit0], nullptr, &firstDigit);
        renderer.WriteTexture(digits[digit1], nullptr, &secondDigit);
    }

    std::string itos(int n)
    {
        constexpr int max_size = std::numeric_limits<int>::digits10 + 1 /*sign*/ + 1 /*0-terminator*/;
        char buffer[max_size] = {0};
        sprintf(buffer, "%d", n);
        return std::string(buffer);
    }

    void TimerFont::MakeTextures(ResourceManager &rm, Renderer &renderer, Color color)
    {
        if (!_font)
        {
            LOG_WARN() << "Empty " << LOG_VALUE(_font) << "\n";
            return;
        }

        const Color dark{ 0,0,0 };
        for (auto n = 0; n < 10; ++n)
        {
            auto str = itos(n);
            _digits[n] = _font->CreateTexture(rm, renderer, str.c_str(), color);
            _darkDigits[n] = _font->CreateTexture(rm, renderer, str.c_str(), dark);
        }
        _rectDigit = _digits[0]->GetBounds();

        _colon = _font->CreateTexture(rm, renderer, ":", color);
        _darkColon = _font->CreateTexture(rm, renderer, ":", dark);
        _rectColon = _colon->GetBounds();
    }
}

