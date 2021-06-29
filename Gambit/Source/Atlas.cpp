#include "Gambit/ThirdParty/SDL.hpp"
#include "Gambit/ThirdParty/Json.hpp"

#include "Gambit/Renderer.hpp"
#include "Gambit/Texture.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Atlas.hpp"

#ifdef WIN32
    // use scoped enums. Can't do this for SDL
    #pragma warning (disable:26812)
#endif

namespace Gambit
{
    using namespace std;

    Atlas::Atlas(TexturePtr const &atlasTexture, const string& spritesJson)
        : _atlasTexture(atlasTexture)
    {
        ReadJsonEx(spritesJson.c_str());
    }

    pair<bool, Rect> Atlas::GetSprite(string const& name) const
    {
        const auto found = _sprites.find(name);
        if (found == _sprites.end())
        {
            SpriteNotFound(name);
            return{ false, Rect{} };
        }
        return { true, found->second };
    }

    pair<bool, Color> Atlas::GetTint(const string& name) const
    {
        const auto found = _tints.find(name);
        if (found == _tints.end())
        {
            TintNotFound(name);
            return { false, Color{} };
        }
        return { true, found->second };
    }

    bool Atlas::WriteSprite(Renderer& renderer, Object const& object) const
    {
        return WriteSprite(renderer, object.Position, object);
    }

    bool Atlas::WriteSprite(Renderer& renderer, const Rect& destRect, Object const &object) const
    {
        const auto [first, second] = GetSprite(object.Sprite);
        if (!first)
            return SpriteNotFound(object.Sprite);
        return WriteRect(renderer, second, destRect, object);
    }

    bool Atlas::WriteSprite(Renderer &renderer, Vector2 const& topLeft, Object const &object) const
    {
        const auto found = GetSprite(object.Sprite);
        if (!found.first)
            return SpriteNotFound(object.Sprite);
        Rect const& dest = found.second;
        return WriteRect(renderer, found.second, Rect(topLeft.x, topLeft.y, dest.width, dest.height), object);
    }

    bool Atlas::WriteRect(Renderer& renderer, Rect const& sourceRect, Rect const& destRect, Object const &object) const
    {
        auto const [found, tint] = GetTint(object.Tint);
        if (found)
            CALL_SDL(SDL_SetTextureColorMod(&_atlasTexture->Get(), tint.red, tint.green, tint.blue));

        CALL_SDL(SDL_RenderCopyEx(
            renderer.GetRenderer(),
            &_atlasTexture->Get(),
            ToSdlRect(sourceRect),
            ToSdlRect(destRect),
            object.Rotation,
            object.Center,
            object.Mirror ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        ));

        if (found)
            CALL_SDL(SDL_SetTextureColorMod(&_atlasTexture->Get(), 255, 255, 255));

        return _result == 0;
    }

    shared_ptr<Atlas> Atlas::LoadAtlas(ResourceManager &resources, Renderer &renderer, string const& baseName, ResourceId const& id)
    {
        const string fileName = baseName + ".png";
        string spritesName = baseName + ".json";

        if (const auto flags = IMG_INIT_PNG; flags != IMG_Init(flags))
        {
            LOG_ERROR() << "Failed to initialise image lib " << IMG_GetError() << "\n";
            return nullptr;
        }

        SDL_Surface *surface = IMG_Load(fileName.c_str());
        if (!surface)
        {
            LOG_ERROR() << "Failed to load " << LOG_VALUE(fileName) << LOG_VALUE(IMG_GetError()) <<  "\n";
            return nullptr;
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
            _spritesNotFound.insert(name);
            return false;
        }

        return false;
    }

    bool Atlas::TintNotFound(const string& name) const
    {
        if (_tintsNotFound.find(name) != _tintsNotFound.end())
        {
            LOG_ERROR() << "No tint named '" << name << "' found\n.";
            _tintsNotFound.insert(name);
            return false;
        }

        return false;
    }

    Rect Atlas::ReadRect(Json &json, const char* name)
    {
        if (!json.contains(name))
        {
            LOG_ERROR() << "Failed to read rect '" << name << "' element from atlas.\n";
            return Rect();
        }

        auto const &rc = json[name].get<vector<int>>();
        return Rect(rc[0], rc[1], rc[2], rc[3]);
    }

    Color Atlas::ReadColor(Json &json, const char *name)
    {
        if (!json.contains(name))
        {
            LOG_ERROR() << "Failed to read color '" << name << "' element from atlas.\n";
            return Color();
        }

        auto const &rc = json[name].get<vector<int>>();
        return Color(rc[0], rc[1], rc[2]);
    }

    bool Atlas::ParseJson(JsonNext &item)
    {
        auto& name = item.key();
        auto& value = item.value();
        auto& type = value["type"];

        if (type == "sprite")
        {
            _sprites[name] = ReadRect(value, "location");
            return true;
        }

        if (type == "tint_list")
        {
            auto const tintNames = 
            { 
                "active_player", "inactive_player", "low_time_inactive", "low_time_active",
                "button_pressed", "time_bar_green", "time_bar_red", "white" 
            }; 

            for (auto const &tint : tintNames)
            {
                _tints[tint] = ReadColor(value, tint);
            }

            return true;
        }

        LOG_ERROR() << "Unknown atlas type '" << type << "'\n";

        return false;
    }
}

