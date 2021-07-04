#pragma once

#include <set>

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

        mutable int _result { 0 };
        mutable std::set<string> _spritesNotFound;
        mutable std::set<string> _tintsNotFound;
        TexturePtr _atlasTexture;
        Sprites _sprites;
        TintList _tints;

    public:
        Atlas(TexturePtr atlasTexture, const string &spritesJson);

        std::pair<bool, Rect> GetSprite(string const &name) const;
        bool WriteSprite(Renderer &, Object const &object) const;
        bool WriteSprite(Renderer &, Rect const &destRect, Object const &) const;

        template <class ...Args>
        static shared_ptr<Atlas> Load(std::string const& baseName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            auto* renderer = std::get<1>(tuple);
            return LoadAtlas(*resources, *renderer, baseName, id);
        }

        bool WriteSprite(Renderer &, Vector2 const &topLeft, Object const &) const;
        bool WriteRect(Renderer &, Rect const &sourceRect, Rect const &destRect, Object const &) const;

        std::pair<bool, Color> GetTint(const string& name) const;

        bool SpriteNotFound(const string& name) const;
        bool TintNotFound(const string& name) const;

        static Rect ReadRect(Json &json, const char *name);
        static Color ReadColor(Json &json, const char *name);

        bool ParseJson(JsonNext &item) override;

    private:
        static shared_ptr<Atlas> LoadAtlas(ResourceManager &, Renderer &, string const& baseName, ResourceId const& id);
    };
}

