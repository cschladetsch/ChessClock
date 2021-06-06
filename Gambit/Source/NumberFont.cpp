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

    void NumberFont::DrawDigits(Renderer& renderer, Vector2 const& topleft, char number) const
    {
        DrawDigits(renderer, Rect{ (int)topleft.x, (int)topleft.y, _rectDigit.width * 2, _rectDigit.height }, number);
    }

    void NumberFont::DrawDigits(Renderer &renderer, Rect const& rect, char number) const
    {
        auto halfWidth = rect.width / 2;
        Rect firstDigit { rect.left, rect.top, halfWidth, rect.height };
        Rect secondDigit { rect.left + halfWidth, rect.top, halfWidth, rect.height };
        
        auto digit0 = number / 10;
        auto digit1 = number % 10;

        renderer.WriteTexture(_digits[digit0], nullptr, &firstDigit);
        renderer.WriteTexture(_digits[digit1], nullptr, &secondDigit);
    }

    void NumberFont::MakeDigitsTextures(ResourceManager &rm, Renderer &renderer, Color color)
    {
        char number[2];
        for (auto n = 0; n < 10; ++n)
        {
            itoa(n, number, 10);
            _digits[n] = _font->DrawText(rm, renderer, number, { color.red, color.green, color.blue });
            int width, height;
            SDL_QueryTexture(&_digits[n]->Get(), 0, 0, &width, &height);
        }

        int width, height;
        SDL_QueryTexture(&_digits[0]->Get(), 0, 0, &width, &height);
        for (auto n = 0; n < 10; ++n)
        {
            int w, h;
            SDL_QueryTexture(&_digits[n]->Get(), 0, 0, &w, &h);
            if (width != w || height != h)
            {
                LOG_WARN() << " not using fixed-width font\n";
            }
        }
        _rectDigit = { 0,0,width,height };
    }
}
