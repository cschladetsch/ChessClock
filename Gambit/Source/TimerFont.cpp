#include "Gambit/TimerFont.hpp"
#include "Gambit/Color.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/ThirdParty/SDL.hpp"

namespace Gambit
{
    TimerFont::TimerFont(ResourceId const& id, FontPtr font)
        : ResourceBase(id), _font(font), DarkOffset(7,9)
    {
    }

    void TimerFont::DrawTime(Renderer& renderer, Vector2 topLeft, uint8_t minutes, uint8_t seconds) const
    {
        DrawTime(renderer, _darkDigits, _darkColon, topLeft + DarkOffset, minutes, seconds);
        DrawTime(renderer, _digits, _colon, topLeft, minutes, seconds);
    }

    void TimerFont::DrawTime(Renderer& renderer, Digits const& digits, TexturePtr colon,  Vector2 topLeft, uint8_t minutes, uint8_t seconds) const
    {
        auto tl = topLeft;
        DrawDigitPair(renderer, digits, tl, minutes);
        tl.x += _rectDigit.width * 2;
        DrawColon(renderer, colon, tl);
        tl.x += _rectColon.width;
        DrawDigitPair(renderer, digits, tl, seconds);
        tl.x += _rectDigit.width * 2;
    }

    Vector2 TimerFont::DrawColon(Renderer &renderer, TexturePtr colon, Vector2 const& topLeft) const
    {
        Rect rect{ topLeft.x, topLeft.y, _rectColon.width, _rectColon.height };
        renderer.WriteTexture(colon, nullptr, &rect);
        return topLeft + Vector2(_rectColon.left + topLeft.x, topLeft.y);
    }

    Vector2 TimerFont::DrawDigitPair(Renderer &renderer, Digits const &digits, Vector2 const& topleft, uint8_t number) const
    {
        if (number > 99)
        {
            LOG_WARN() << "attempt to two-digit draw number with " << LOG_VALUE(number) << "\n";
        }

        number %= 100;

        Rect firstDigit{ topleft.x, topleft.y, _rectDigit.width, _rectDigit.height };
        Rect secondDigit{ topleft.x + _rectDigit.width, topleft.y, _rectDigit.width, _rectDigit.height };
        
        auto digit0 = number / 10;
        auto digit1 = number % 10;

        renderer.WriteTexture(digits[digit0], nullptr, &firstDigit);
        renderer.WriteTexture(digits[digit1], nullptr, &secondDigit);

        return Vector2(secondDigit.left + _rectDigit.width*2, _rectDigit.height);
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
        Color dark{ 0,0,0 };
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

