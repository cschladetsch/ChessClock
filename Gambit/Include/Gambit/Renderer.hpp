#pragma once

#include "Gambit/Rect.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class Renderer
    {
    public:
        const int Width = 800;
        const int Height = 480;

    private:
        Logger _log { "TheRenderer "};
        SDL_Window *_window{ nullptr };
        SDL_Renderer *_renderer{ nullptr };
        int _frameNumber{ 0 };
        mutable int _result{ 0 };

    public:
        SDL_Window *GetWindow() const { return _window; }
        SDL_Renderer *GetRenderer() const { return _renderer; }

        Renderer();
        ~Renderer();

        bool Construct(const char *title);
        void Destroy();

        bool Clear();
        bool Present();

        bool WriteTexture(TexturePtr const &texture, Vector2 const &topLeft) const;
        bool WriteTexture(TexturePtr const &texture, Rect const *source, Rect const *dest) const;
        bool WriteTexture(TexturePtr const &texture, Vector2 const &topLeft, Color const &tint) const;

        int GetFrameNumber() const { return _frameNumber; }
    };
}

