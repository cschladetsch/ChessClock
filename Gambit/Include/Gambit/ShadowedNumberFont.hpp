#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/NumberFont.hpp"

namespace Gambit
{
    class ShadowedFont
        //: public Font
    {
        Color _back;
        Vector2 _offset;

    public:
        ShadowedFont(ResourceId const& id, FontPtr font, Color back, Vector2 offset);

        //TexturePtr CreateTexture(ResourceManager &, Renderer &, const char *text, Color fore) const override;
    };
}
