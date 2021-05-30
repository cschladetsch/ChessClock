#pragma once

#include "ChessClock/Context.hpp"

namespace ChessClock::TestScene
{
    struct Values
    {
        FontPtr font;
        TexturePtr background;
        TexturePtr text;
        Rect bounds;
    };

    typedef Context<Values> Ctx;

    bool TestSetup(Ctx &);
    bool TestStep(Ctx &);
    bool TestProcessEvents(Ctx &);
}
