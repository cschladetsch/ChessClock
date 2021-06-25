#include <set>

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

    static set<string> _spritesNotFound;
    static set<string> _tintsNotFound;

    Atlas::Atlas(TexturePtr texture, const string& spritesName)
        : _atlasTexture(texture)
    {
        ReadJsonEx(spritesName.c_str());
    }

    pair<bool, Rect> Atlas::GetSprite(string const& name) const
    {
        auto found = _sprites.find(name);
        if (found == _sprites.end())
        {
            SpriteNotFound(name);
            return make_pair(false, Rect{});
        }
        return make_pair(true, found->second);
    }

    std::pair<bool, Color> Atlas::GetTint(const string& name) const
    {
        auto found = _tints.find(name);
        if (found == _tints.end())
        {
            TintNotFound(name);
            return { false, Color() };
        }
        return std::make_pair(true, found->second);
    }

    bool Atlas::WriteSprite(Renderer& renderer, Object const& object) const
    {
        return WriteSprite(renderer, object.Sprite, object.Position, object.Tint, object.Mirror);
    }

    bool Atlas::WriteSprite(Renderer& renderer, string const& name, const Rect& destRect, bool mirror) const
    {
        auto found = GetSprite(name);
        if (!found.first)
            return SpriteNotFound(name);
        return WriteRect(renderer, found.second, destRect);
    }

    bool Atlas::WriteSprite(Renderer &renderer, string const& name, Vector2 const& topLeft, bool mirror) const
    {
        auto found = GetSprite(name);
        if (!found.first)
            return SpriteNotFound(name);
        Rect const& dest = found.second;
        return WriteRect(renderer, found.second, Rect(topLeft.x, topLeft.y, dest.width, dest.height));
    }

    bool Atlas::WriteSprite(Renderer& renderer, string const& name, const Vector2& destPoint, const string& tintName, bool mirror) const
    {
        auto found = GetSprite(name);
        if (!found.first)
            return SpriteNotFound(name);
        auto rect = found.second;

        auto tint = Colors::White;
        if (!tintName.empty())
        {
            auto tintFound = GetTint(tintName);
            if (!tintFound.first)
                return TintNotFound(tintName);
            tint = tintFound.second;
        }

        return WriteRect(renderer, found.second, Rect{ destPoint.x, destPoint.y, rect.width, rect.height }, tint, mirror);
    }

    bool Atlas::WriteRect(Renderer &renderer, const Rect& sourceRect, const Rect& destRect, Color const& tint, bool mirror) const
    {
        int result = 0;
        CALL_SDL(SDL_SetTextureColorMod(&_atlasTexture->Get(), tint.red, tint.green, tint.blue));
        if (!WriteRect(renderer, sourceRect, destRect, mirror))
        {
            LOG_ERROR() << LOG_VALUE(sourceRect) << LOG_VALUE(destRect) << '\n';
            return false;
        }
        CALL_SDL(SDL_SetTextureColorMod(&_atlasTexture->Get(), 255, 255, 255));
        return result == 0;
    }

    bool Atlas::WriteRect(Renderer& renderer, Rect const& sourceRect, Rect const& destRect, bool mirror) const
    {
        int result = 0;
        CALL_SDL(SDL_RenderCopyEx(
            renderer.GetRenderer(),
            &_atlasTexture->Get(),
            ToSdlRect(sourceRect),
            ToSdlRect(destRect),
            0, // angle
            nullptr, // center
            mirror ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        ));

        return result == 0;
    }

    shared_ptr<Atlas> Atlas::LoadAtlas(ResourceManager &resources, Renderer &renderer, string const& baseName, ResourceId const& id)
    {
        string fileName = baseName + ".png";
        string spritesName = baseName + ".json";

        auto flags = IMG_INIT_PNG;
        if (flags != IMG_Init(flags))
        {
            LOG_ERROR() << "Failed to initialise image lib " << IMG_GetError() << "\n";
            return 0;
        }

        SDL_Surface *surface = IMG_Load(fileName.c_str());
        if (!surface)
        {
            LOG_ERROR() << "Failed to load " << LOG_VALUE(fileName) << LOG_VALUE(IMG_GetError()) <<  "\n";
            return 0;
        }

        uint32_t key;
        if (SDL_GetColorKey(surface, &key) == 0)
        {
            SDL_SetColorKey(surface, SDL_RLEACCEL, key);
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        SDL_FreeSurface(surface);

        auto ptr = make_shared<Texture>(resources.NewId(), texture);
        resources.AddResource(ptr->GetResourceId(), ptr);

        return make_shared<Atlas>(ptr, spritesName);
    }

    bool Atlas::SpriteNotFound(const string& name) const
    {
        if (_spritesNotFound.find(name) != _spritesNotFound.end())
        {
            LOG_ERROR() << "No sprite named '" << name << "' found\n.";
            return false;
        }
        _spritesNotFound.insert(name);
        return false;
    }

    bool Atlas::TintNotFound(const string& name) const
    {
        static set<string> notFound;
        if (_tintsNotFound.find(name) != _tintsNotFound.end() && notFound.find(name) == notFound.end())
        {
            LOG_ERROR() << "No tint named '" << name << "' found\n.";
            notFound.insert(name);
            return false;
        }

        _tintsNotFound.insert(name);
        return false;
    }

    Rect Atlas::GetRect(Json& json, const char* name)
    {
        if (!json.contains(name))
        {
            LOG_ERROR() << "Failed to read rect '" << name << "' element from atlas.\n";
            return Rect();
        }

        auto const& rc = json[name].get<vector<int>>();
        return Rect(rc[0], rc[1], rc[2], rc[3]);
    }

    Color Atlas::GetColor(Json & json, const char *name)
    {
        if (!json.contains(name))
        {
            LOG_ERROR() << "Failed to read color '" << name << "' element from atlas.\n";
            return Color();
        }

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
            auto names = 
            { 
                "active_player", "foo", "inactive_player", "low_time_inactive", "low_time_active",
                "button_pressed", "time_bar_green", "time_bar_red", "white" 
            };
            for (auto const &name : names)
            {
                _tints[name] = GetColor(value, name);
            }

            return true;
        }

        LOG_ERROR() << "Unknown atlas type '" << type << "'\n";

        return false;
    }
}

