#include "SDL_image.h"

#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/ThirdParty/Json.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/Atlas.hpp"
#include "Gambit/Exceptions.hpp"

namespace Gambit
{
    using nlohmann::json;

    Atlas::Atlas(TexturePtr texture, const string& spritesName)
        : _atlasTexture(texture)
    {
        if (!ReadSprites(spritesName))
        {
            LOG_ERROR() << "Failed to sprites from " << LOG_VALUE(spritesName) << "\n";
        }
    }

    Rect GetRect(nlohmann::json& json, const char* name)
    {
        auto const& rc = json[name].get<std::vector<int>>();
        return Rect(rc[0], rc[1], rc[2], rc[3]);
    }

    Color GetColor(nlohmann::json& json, const char* name)
    {
        auto const& rc = json[name].get<std::vector<int>>();
        return Color(rc[0], rc[1], rc[2]);
    }

    bool Atlas::ReadSprites(const string& fileName)
    {
        std::ifstream inFile(fileName.c_str());
        if (!inFile)
        {
            LOG_ERROR() << "Couldn't load json from " << LOG_VALUE(fileName) << "\n";
            return false;
        }

        try
        {
            json j;
            inFile >> j;
            for (auto& item : j.items())
            {
                auto& name = item.key();
                auto& value = item.value();
                auto& type = value["type"];
                if (type == "sprite")
                {
                    _sprites[name] = GetRect(value, "location");
                    continue;
                }

                if (type == "tint_list")
                {
                    _tintList["active_player"] = GetColor(value, "active_player");
                    _tintList["low_time_inactive"] = GetColor(value, "low_time_inactive");
                    _tintList["low_time_active"] = GetColor(value, "low_time_active");
                    _tintList["button_pressed"] = GetColor(value, "button_pressed");
                }
            }

            return true;
        }
        catch (std::exception& e)
        {
            LOG_ERROR() << "Error reading json " << LOG_VALUE(fileName) << "\n";
            LOG_ERROR() << "Error reading json " << e.what() << "\n";
            return false;
        }

        return false;
    }

    std::pair<bool, Rect> Atlas::GetSprite(string const& name) const
    {
        auto found = _sprites.find(name);
        if (found == _sprites.end())
        {
            LOG_WARN() << "No sprite named " << name << " found\n.";
            return std::make_pair(false, Rect{});
        }
        return std::make_pair(true, found->second);
    }

    bool Atlas::WriteSprite(Renderer& renderer, string const& name, const Vector2& topLeft) const
    {
        auto found = GetSprite(name);
        auto destRect = Rect{ topLeft.x, topLeft.y, found.second.width, found.second.height };
        return !found.first ? false : WriteSprite(renderer, found.second, destRect);
    }

    bool Atlas::WriteSprite(Renderer& renderer, string const& name, const Rect& destRect) const
    {
        auto found = GetSprite(name);
        if (!found.first)
        {
            LOG_ERROR() << "Sprite " << name << " not found\n";
            return false;
        }
        return WriteSprite(renderer, found.second, destRect);
    }

    bool Atlas::WriteSprite(Renderer& renderer, Rect const& sourceRect, Rect const& destRect) const
    {
        auto result = SDL_RenderCopyEx(
            renderer.GetRenderer(),
            &_atlasTexture->Get(),
            ToSdlRect(sourceRect),
            ToSdlRect(destRect),
            0, // angle
            nullptr, // center
            SDL_FLIP_NONE // renderFlip
        );
        if (result != 0)
        {
            LOG_ERROR() << "WriteSprite: " << LOG_VALUE(SDL_GetError()) << "\n";
            return false;
        }
        return true;
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
