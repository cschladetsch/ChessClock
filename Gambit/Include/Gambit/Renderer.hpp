#pragma once

#include "Gambit/Rect.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class Renderer
    {
        const int Width = 800;
        const int Height = 480;

        Logger _log { "Renderer "};
        SDL_Window *_window = 0;
        SDL_Renderer *_renderer = 0;
        int _frameNumber{ 0 };
        mutable int _result = 0;

    public:
        SDL_Window *GetWindow() const { return _window; }
        SDL_Renderer *GetRenderer() const { return _renderer; }

    public:
        Renderer();
        ~Renderer();

        bool Construct(const char *title);
        void Destroy();

        bool Clear();
        bool Present();

        bool WriteTexture(TexturePtr texture, Vector2 const &topLeft) const;
        bool WriteTexture(TexturePtr texture, Rect const *source, Rect const *dest) const;
        bool WriteTexture(TexturePtr texture, Vector2 const &topLeft, Color const &tint) const;

        int GetFrameNumber() const { return _frameNumber; }
    };
}

