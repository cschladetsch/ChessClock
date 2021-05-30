#include <string>
#include <fstream>
#include <streambuf>

#include <iostream>

#include "ChessClock/ThirdParty/ssfn.h"
#include "ChessClock/Font.hpp"
#include "ChessClock/Renderer.hpp"
#include "ChessClock/ResourceManager.hpp"
#include "ChessClock/Texture.hpp"

#include "ChessClock/SDL_ttf.hpp"

namespace ChessClock
{
    shared_ptr<Font> Font::LoadFont(std::string const &fileName, ResourceId const &id, int pointSize)
    {
        TTF_Init();
        _TTF_Font *font = TTF_OpenFont(fileName.c_str(), pointSize);
        return std::make_shared<Font>(id, font);
    }

    void Font::Deleter(_TTF_Font* font)
    {
        TTF_CloseFont(font);
    }

    shared_ptr<Texture> Font::DrawText(ResourceManager &rm, Renderer &renderer, const char *text, SDL_Color color) const
    {
        // TODO: cache
        SDL_Surface *surface = TTF_RenderText_Solid(const_cast<_TTF_Font *>(&Get()), text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        SDL_FreeSurface(surface);
        return std::make_shared<Texture>(rm.NewId(), texture);
    }
}
