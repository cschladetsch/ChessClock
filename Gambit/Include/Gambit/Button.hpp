#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Event.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/ResourceBase.hpp"

namespace Gambit
{
    class Button
        : public ResourceBase
    {
        TexturePtr _texture;
        Rect _rect;

    public:
        Event<Button> Pressed;
        Event<Button> Relased;

        Button() = default;
        Button(FontPtr font, string text, SpritePtr background);

        Rect const& GetRect() const { return _rect; }
        TexturePtr GetTexture() const { return _texture; }
    };
}
