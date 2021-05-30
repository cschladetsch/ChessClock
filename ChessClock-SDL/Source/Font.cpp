#include <string>
#include <fstream>
#include <streambuf>

#include <iostream>

#include "ChessClock/ThirdParty/ssfn.h"
#include "ChessClock/Font.hpp"
#include "ChessClock/Renderer.hpp"

#include "SDL.h"

#ifdef WIN32
#include "SDL_ttf.h"
#else
#include "SDL2/SDL_ttf.h"
#endif

namespace ChessClock
{
    std::shared_ptr<Font> Font::LoadFont(std::string const &folder, std::string const &name, int ptsize)
    {
        TTF_Init();

        //std::string fileName(folder + "\\" + name);
        _TTF_Font *font = TTF_OpenFont(name.c_str(), ptsize);
        return std::make_shared<Font>(font);
    }

    Font::Font(_TTF_Font *font)
        : _font(font)
    {
    }

    SDL_Texture *Font::DrawText(Renderer &renderer, const char *text, SDL_Color color) const
    {
        // TODO: cache
        SDL_Surface *surface = TTF_RenderText_Solid(_font, text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        SDL_FreeSurface(surface);
        return texture;
    }
}
