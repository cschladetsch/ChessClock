#pragma once

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/Logger.hpp"
#include "ChessClock/Rect.hpp"

namespace ChessClock
{
    class Renderer
    {
        Logger _log { "Renderer "};
        SDL_Window *_window = 0;
        SDL_Renderer *_renderer = 0;

    public:
        SDL_Window *GetWindow() const { return _window; }
        SDL_Renderer *GetRenderer() const { return _renderer; }

        Renderer();
        ~Renderer();

        bool Construct(const char *title);
        void Destroy();

        void Clear();
        void Present();

        bool WriteTexture(TexturePtr texture, Rect const *source, Rect const *dest) const;
    };
}

