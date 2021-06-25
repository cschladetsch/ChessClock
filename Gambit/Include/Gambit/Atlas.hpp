#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Color.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/JsonReader.hpp"

namespace Gambit
{
    class Atlas
        : public ResourceBase
        , JsonReader<Atlas>
    {
        static inline Logger _log{ "Atlas" };

        typedef std::unordered_map<string, Rect> Sprites;
        typedef std::unordered_map<string, Color> TintList;

        TexturePtr _atlasTexture;
        Sprites _sprites;
        TintList _tints;

    public:
        Atlas(TexturePtr atlasTexture, const string &spritsJson);

        std::pair<bool, Rect> GetSprite(string const &name) const;

        bool WriteSprite(Renderer &, string const &name, const Rect &destRect, bool mirror = false) const;
        bool WriteSprite(Renderer &, string const &name, const Vector2 &topLeft, bool mirror = false) const;
        bool WriteSprite(Renderer &, string const &name, const Vector2 &destPoint, const string &tintName, bool mirror = false) const;
        bool WriteSprite(Renderer &, Object const &object) const;

        template <class ...Args>
        static shared_ptr<Atlas> Load(std::string const& baseName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            auto* renderer = std::get<1>(tuple);
            return LoadAtlas(*resources, *renderer, baseName, id);
        }

    private:
        static shared_ptr<Atlas> LoadAtlas(ResourceManager &, Renderer &, string const& baseName, ResourceId const& id);

        bool SpriteNotFound(const string& name) const;
        bool TintNotFound(const string& name) const;

        std::pair<bool, Color> GetTint(const string& name) const;

        bool WriteRect(Renderer &, Rect const &sourceRect, Rect const &destRect, bool mirror = false) const;
        bool WriteRect(Renderer &, Rect const &sourceRect, Rect const &destRect, Color const& tint, bool mirror = false) const;

        Rect GetRect(Json &json, const char *name);
        Color GetColor(Json &json, const char *name);
        bool ParseJson(JsonNext &item);
    };
}
