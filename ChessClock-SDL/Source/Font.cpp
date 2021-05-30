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
    std::shared_ptr<Font> Font::Load(std::string const &folder, std::string const &name)
    {
        TTF_Init();

        //std::string fileName(folder + "\\" + name);
        _TTF_Font *font = TTF_OpenFont(name.c_str(), 100);
        return std::make_shared<Font>(font);
    }

    Font::Font(_TTF_Font *font)
        : _font(font)
    {
    }

    void Font::SetSize(int ptsize) const
    {
#ifdef WIN32
        TTF_SetFontSize(_font, ptsize);
#endif
    }

    void Font::SetDpi(int ptsize, int hdpi, int vdpi) const
    {
#ifdef WIN32
        TTF_SetFontSizeDPI(_font, ptsize, hdpi, vdpi);
#endif
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
