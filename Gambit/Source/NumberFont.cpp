#include "Gambit/NumberFont.hpp"
#include "Gambit/Color.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/ThirdParty/SDL.hpp"

namespace Gambit
{
    NumberFont::NumberFont(ResourceId const& id, FontPtr font)
        : ResourceBase(id), _font(font)
    {
    }

    void NumberFont::DrawTime(Renderer&, Vector2 topLeft, uint8_t minutes, uint8_t seconds) const
    {
    }

    void NumberFont::DrawTime(Renderer &renderer, Vector2 topLeft, uint8_t minutes, uint8_t seconds, uint8_t millis) const
    {
        DrawDigitPair(renderer, topLeft, minutes);
        topLeft.x += _rectDigit.width * 2;
        DrawColon(renderer, topLeft);
        topLeft.x += _rectColon.width;
        DrawDigitPair(renderer, topLeft, seconds);
        topLeft.x += _rectDigit.width * 2;
        DrawColon(renderer, topLeft);
        topLeft.x += _rectColon.width;
        DrawDigitPair(renderer, topLeft, millis);
    }

    void NumberFont::DrawColon(Renderer &renderer, Vector2 const& topLeft) const
    {
        Rect rect{ (int)topLeft.x, (int)topLeft.y, _rectColon.width, _rectColon.height };
        renderer.WriteTexture(_colon, nullptr, &rect);
    }

    void NumberFont::DrawDigitPair(Renderer &renderer, Vector2 const& topleft, uint8_t number) const
    {
        number %= 100;

        Rect firstDigit{ (int)topleft.x, (int)topleft.y, _rectDigit.width, _rectDigit.height };
        Rect secondDigit{ (int)topleft.x + (int)_rectDigit.width, (int)topleft.y, _rectDigit.width, _rectDigit.height };
        
        auto digit0 = number / 10;
        auto digit1 = number % 10;

        renderer.WriteTexture(_digits[digit0], nullptr, &firstDigit);
        renderer.WriteTexture(_digits[digit1], nullptr, &secondDigit);

    }

    void NumberFont::MakeTextures(ResourceManager &rm, Renderer &renderer, Color color)
    {
        char number[2];
        SDL_Color sdlColor{ color.red, color.green, color.blue };
        for (auto n = 0; n < 10; ++n)
        {
            itoa(n, number, 10);
            _digits[n] = _font->DrawText(rm, renderer, number, sdlColor);
        }

        _colon = _font->DrawText(rm, renderer, ":", sdlColor);

        _rectColon = _colon->GetBounds();
        _rectDigit = _digits[0]->GetBounds();
    }
}
