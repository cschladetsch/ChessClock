#include "Gambit/NumberFont.hpp"
#include "Gambit/Color.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/ThirdParty/SDL.hpp"

namespace Gambit
{
    NumberFont::NumberFont(ResourceId const& id, _TTF_Font* font)
        : Font(id, font)
    {
    }

    void NumberFont::DrawDigits(Renderer &renderer, Rect const& rect, char number) const
    {
        auto halfWidth = rect.width / 2;
        Rect firstDigit { rect.top, rect.left, halfWidth, rect.height };
        Rect secondDigit { rect.top, rect.left + halfWidth, halfWidth, rect.height };
        
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
            _itoa(n, number, 10);
            _digits[n] = DrawText(rm, renderer, number, { color.red, color.green, color.blue });
        }

        int width, height;
        SDL_QueryTexture(&_digits[0]->Get(), 0, 0, &width, &height);
        _rectDigit = { 0,0,width,height };
    }
}
