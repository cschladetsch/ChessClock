#pragma once

#include "Gambit/Component.hpp"
#include "Gambit/Event.hpp"

namespace Gambit
{
    class Button
        : Component
    {
        TexturePtr _text;

    public:
        Event<Button> Pressed;
        Event<Button> Relased;

        Button() { }
        Button(FontPtr font, string text);
    };
}
