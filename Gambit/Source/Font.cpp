#include "Gambit/Font.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/ThirdParty/SDL_ttf.hpp"

namespace Gambit
{
    shared_ptr<Font> Font::LoadFont(std::string const &fileName, ResourceId const &id, int pointSize)
    {
        _TTF_Font *font = TTF_OpenFont(fileName.c_str(), pointSize);
        return std::make_shared<Font>(id, font);
    }

    void Font::Deleter(_TTF_Font* font)
    {
        TTF_CloseFont(font);
    }

    TexturePtr Font::CreateTexture(ResourceManager &rm, Renderer &renderer, const char *text, SDL_Color color) const
    {
        // TODO: cache
        SDL_Surface *surface = TTF_RenderText_Solid(const_cast<_TTF_Font *>(&Get()), text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        SDL_FreeSurface(surface);
        return std::make_shared<Texture>(rm.NewId(), texture);
    }
}
