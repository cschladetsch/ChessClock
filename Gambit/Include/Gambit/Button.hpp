#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Event.hpp"

namespace Gambit
{
    class Button
    {
        TexturePtr _text;

    public:
        Event<Button> Pressed;
        Event<Button> Relased;

        Button() { }
        Button(FontPtr font, string text);
    };
}
