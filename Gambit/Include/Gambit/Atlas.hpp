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
        , public JsonReader
    {
        static inline Logger _log{ "Atlas" };

        typedef std::unordered_map<string, Rect> Sprites;
        typedef std::unordered_map<string, Color> TintList;
        typedef JsonReader::JsonNext JsonNext;

        TexturePtr _atlasTexture;
        Sprites _sprites;
        TintList _tints;
        mutable std::set<string> _tintsNotFound;

    public:
        Atlas(TexturePtr atlasTexture, const string &spritsJson);

        std::pair<bool, Rect> GetSprite(string const &name) const;

        bool WriteSprite(Renderer &, string const &name, const Rect &destRect) const;
        bool WriteSprite(Renderer &, string const &name, const Vector2 &topLeft) const;
        bool WriteSprite(Renderer &, string const &name, const Vector2 &destPoint, const string &tintName) const;

        bool WriteRect(Renderer &, Rect const &sourceRect, const Vector2 &destPoint, Color const &color) const;
        //bool WriteSprite(Renderer &, string const& name, const Vector2& destRect, const string& tintName) const;
        //bool WriteSprite(Renderer &, string const &name, Rect const &sourceRect, Rect const &destRect, Color const &) const;

        template <class ...Args>
        static shared_ptr<Atlas> Load(std::string const& baseName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            auto* renderer = std::get<1>(tuple);
            return LoadAtlas(resources, *renderer, baseName, id);
        }

    private:
        bool SpriteNotFound(const string& name) const;
        bool TintNotFound(const string& name) const;

        std::pair<bool, Color> GetTint(const string& name) const;

        static shared_ptr<Atlas> LoadAtlas(ResourceManager &, Renderer &, string const& baseName, ResourceId const& id);
        bool WriteSprite(Renderer &, Rect const &sourceRect, Rect const &destRect) const;
        bool ReadSprites(const string &fileName);

        bool ParseJson(JsonNext &item);
    };
}
