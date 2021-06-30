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
        if (!font)
        {
            LOG_ERROR() << "Failed to load font " << fileName << "\n";
            return 0;
        }
        LOG_INFO() << "Loaded font " << LOG_VALUE(fileName) << LOG_VALUE(pointSize) << "\n";
        return std::make_shared<Font>(id, font);
    }

    void Font::Deleter(_TTF_Font *font)
    {
        TTF_CloseFont(font);
    }

    TexturePtr Font::CreateTexture(ResourceManager &rm, Renderer &renderer, std::string const &text, Color color) const
    {
        auto key = std::make_pair(std::string(text), color);
        auto found = _cache.find(key);
        if (found != _cache.end())
        {
            return found->second;
        }

        SDL_Surface* surface = TTF_RenderText_Solid(const_cast<_TTF_Font *>(&Get()), text.c_str(), { color.red, color.green, color.blue, color.alpha });
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        SDL_FreeSurface(surface);

        return _cache[key] = std::make_shared<Texture>(ResourceId(), texture);
    }
}

