#pragma once

#include <SDL.h>

#include "ChessClock/Logger.hpp"

namespace ChessClock
{
    class Renderer
    {
    private:
        Logger _log { "Renderer "};
        SDL_Window* _window = 0;
        SDL_Renderer *_renderer = 0;

    public:
        SDL_Window* GetWindow() const { return _window; }
        SDL_Renderer* GetRenderer() const { return _renderer; }

        Renderer();
        bool Construct();
        void Destroy();
        void Clear();
        void Present();
    };
}

