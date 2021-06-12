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
    using namespace std;
    using nlohmann::json;

    Atlas::Atlas(TexturePtr texture, const string& spritesName)
        : _atlasTexture(texture)
    {
        if (!ReadJson(spritesName.c_str()))
        {
            LOG_ERROR() << "Failed to sprites from " << LOG_VALUE(spritesName) << "\n";
        }
    }

    Rect GetRect(nlohmann::json& json, const char* name)
    {
        auto const& rc = json[name].get<vector<int>>();
        return Rect(rc[0], rc[1], rc[2], rc[3]);
    }

    Color GetColor(nlohmann::json& json, const char* name)
    {
        auto const& rc = json[name].get<vector<int>>();
        return Color(rc[0], rc[1], rc[2]);
    }

    bool Atlas::ParseJson(JsonNext& item)
    {
        auto& name = item.key();
        auto& value = item.value();
        auto& type = value["type"];
        if (type == "sprite")
        {
            _sprites[name] = GetRect(value, "location");
            return true;
        }

        if (type == "tint_list")
        {
            _tints["active_player"] = GetColor(value, "active_player");
            _tints["low_time_inactive"] = GetColor(value, "low_time_inactive");
            _tints["low_time_active"] = GetColor(value, "low_time_active");
            _tints["button_pressed"] = GetColor(value, "button_pressed");
        }

        return false;
    }

    set<string> _notFound;

    pair<bool, Rect> Atlas::GetSprite(string const& name) const
    {
        auto found = _sprites.find(name);
        if (found == _sprites.end())
        {
            if (_notFound.find(name) == _notFound.end())
            {
                SpriteNotFound(name);
                _notFound.insert(name);
            }
            return make_pair(false, Rect{});
        }
        return make_pair(true, found->second);
    }

    std::pair<bool, Color> Atlas::GetTint(const string& name) const
    {
        auto found = _tints.find(name);
        if (found == _tints.end())
        {
            LOG_ERROR() << "No tint named " << name << " found\n.";
            _tintsNotFound.insert(name);
            return { false, Color() };
        }
        return std::make_pair(true, found->second);
    }

    bool Atlas::SpriteNotFound(const string& name) const
    {
        LOG_ERROR() << "No sprite named " << name << " found\n.";
        return false;
    }

    bool Atlas::TintNotFound(const string& name) const
    {
        LOG_ERROR() << "No tint named " << name << " found\n.";
        return false;
    }

    bool Atlas::WriteSprite(Renderer& renderer, string const& name, const Vector2& destPoint, const string& tintName) const
    {
        auto found = GetSprite(name);
        if (!found.first)
            return SpriteNotFound(name);

        auto tintFound = GetTint(tintName);
        if (!tintFound.first)
            return TintNotFound(tintName);

        auto texture = found.second;
        auto tint = tintFound.second;

        SDL_SetTextureColorMod(&_atlasTexture->Get(), tint.red, tint.green, tint.blue);
        WriteRect(renderer, found.second, destPoint, tint);
        SDL_SetTextureColorMod(&_atlasTexture->Get(), 255, 255, 255);

        return true;
    }

    bool Atlas::WriteRect(Renderer &renderer, const Rect& sourceRect, const Vector2& destPoint, Color const& color) const
    {
        return false;
    }

    bool Atlas::WriteSprite(Renderer& renderer, string const& name, const Rect& destRect) const
    {
        auto found = GetSprite(name);
        if (!found.first)
            return SpriteNotFound(name);
        return WriteSprite(renderer, found.second, destRect);
    }

    bool Atlas::WriteSprite(Renderer&, string const& name, Vector2 const& topLeft) const
    {
        GAMBIT_NOT_IMPLEMENTED();
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

        auto ptr = make_shared<Texture>(resources.NewId(), texture);
        resources.AddResource(ptr->GetResourceId(), ptr);

        return make_shared<Atlas>(ptr, spritesName);
    }
}
