#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/Rect.hpp"

namespace Gambit
{
    class Renderer
    {
        const int Width = 800;
        const int Height = 480;

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

        bool Clear();
        bool Present();

        bool WriteTexture(TexturePtr texture, Rect const *source, Rect const *dest) const;
        bool WriteTexture(TexturePtr texture, Vector2 const &topLeft) const;
        bool WriteTexture(TexturePtr texture, Vector2 const &topLeft, Gambit::Color const &tint) const;
    };
}

