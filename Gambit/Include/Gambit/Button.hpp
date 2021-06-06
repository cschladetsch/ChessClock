#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Event.hpp"
#include "Gambit/Rect.hpp"

namespace Gambit
{
    class Button
    {
        TexturePtr _text;
        Rect _rect;

    public:
        Event<Button> Pressed;
        Event<Button> Relased;

        Button() { }
        Button(FontPtr font, string text, SpritePtr background);
    };
}
