#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Atlas.hpp"
#include "Gambit/Exceptions.hpp"
#include "SDL_image.h"

namespace Gambit
{
    Atlas::Atlas(TexturePtr texture, const string &spritesName)
        : _atlasTexture(texture)
    {
        if (!ReadSprites(spritesName))
        {
            LOG_ERROR() << "Failed to sprites from " << LOG_VALUE(spritesName) <<  "\n";
        }
    }

    bool Atlas::ReadSprites(const string& fileName)
    {
        return false;
    }

    bool Atlas::WriteSprite(Renderer &renderer, string const& name, TexturePtr texture, const Rect &destRect) const
    {
        auto found = _sprites.find(name);
        if (found == _sprites.end())
        {
            LOG_ERROR() << "No sprite named " << name << " found\n.";
            return false;
        }
        auto srcRect = found->second;
        /*
        SDL_RenderCopyEx(
            texture, 
            &srcRect, 
            &destRect);
            */
        GAMBIT_NOT_IMPLEMENTED_1("WriteSprite");
    }

    shared_ptr<Atlas> Atlas::LoadAtlas(ResourceManager &resources, Renderer &renderer, string const& baseName, ResourceId const& id)
    {
        string fileName = baseName + ".png";
        string spritesName = baseName + ".json";

        auto flags = IMG_INIT_PNG;
        if (!IMG_Init(flags))
        {
            LOG_ERROR() << "Failed to initialise image lib " << IMG_GetError() << "\n";
            return 0;
        }

        SDL_Texture *texture = IMG_LoadTexture(renderer.GetRenderer(), fileName.c_str());
        if (!texture)
        {
            LOG_ERROR() << "Failed to load " << LOG_VALUE(fileName) << LOG_VALUE(IMG_GetError()) <<  "\n";
            return 0;
        }

        auto ptr = std::make_shared<Texture>(resources.NewId(), texture);
        resources.AddResource(ptr->GetResourceId(), ptr);

        return std::make_shared<Atlas>(ptr, spritesName);
    }
}
