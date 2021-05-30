#define SSFN_IMPLEMENTATION
#include <string>
#include <fstream>
#include <streambuf>

#include "ChessClock/ThirdParty/ssfn.h"
#include "ChessClock/Font.hpp"

#include "SDL2/SDL_ttf.h"

namespace ChessClock
{
    std::shared_ptr<Font> Font::Load(std::string const &folder, std::string const &name)
    {
        std::string fileName(folder + "\\" + name);
        std::ifstream t(fileName);
        if (!t)
        {
            return 0;
        }

        t.seekg(0, std::ios::end);   
        auto len = t.tellg();
        char* buffer = new char[len];
        t.seekg(0, std::ios::beg);
        t.read(buffer, len);

        std::shared_ptr<SSFN::Font> font{ new SSFN::Font };
        if (font->Load(buffer) != SSFN_OK)
        {
            delete[] buffer;
            return 0;
        }
        delete[] buffer;
        return std::make_shared<Font>(font);
    }

    Font::Font(std::shared_ptr<SSFN::Font> font)
        : _font(font)
    {
    }

    void Font::DrawText(Renderer&, Vector2 const& startPos, const char* text)
    {
    }
}
