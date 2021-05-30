#include <string>
#include <fstream>
#include <streambuf>

#include "ChessClock/ThirdParty/ssfn.h"
#include "ChessClock/Font.hpp"

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

        std::string fileName(folder + "\\" + name);
        TTF_Font *font = TTF_OpenFont(fileName.c_str(), 16);
        return 0;
    }

    Font::Font(std::shared_ptr<SSFN::Font> font)
        : _font(font)
    {
    }

    void Font::DrawText(Renderer&, Vector2 const& startPos, const char* text)
    {
    }
}
