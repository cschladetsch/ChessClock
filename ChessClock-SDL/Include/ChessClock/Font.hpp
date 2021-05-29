#pragma once

#include "ChessClock/Vector2.hpp"

namespace ChessClock
{
    class Renderer;

    class Font
    {
    public:
        Font(const char* name);

        void DrawText(Renderer &, Vector2 const &startPos, const char *text);
    };
}
