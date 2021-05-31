#pragma once

#include "Gambit/Font.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Color.hpp"

namespace Gambit
{
    class NumberFont
        : public Font
    {
        typedef std::array<TexturePtr, 10> Digits;

        Digits _digits;
        Rect _rectDigit;

    public:
        NumberFont(ResourceId const& id, _TTF_Font* font);

        void DrawDigits(Renderer&, Rect const& destRect, char number) const;

        template <class ...Args>
        static shared_ptr<NumberFont> Load(std::string const& fileName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto &resourceManager = std::get<0>(tuple);
            auto &renderer = std::get<1>(tuple);
            auto pointSize = std::get<2>(tuple);
            Font::Load(fileName, id, pointSize);
            MakeDigitsTextures(resourceManager);
        }

    private:
        void MakeDigitsTextures(ResourceManager &, Renderer &, Color);
    };
}
