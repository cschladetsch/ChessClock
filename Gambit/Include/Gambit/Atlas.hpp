#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/Color.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    class Atlas
        : public ResourceBase
    {
        static inline Logger _log{ "Atlas" };

        typedef std::unordered_map<string, Rect> Sprites;
        typedef std::unordered_map<string, Color> TintList;

        TexturePtr _atlasTexture;;
        Sprites _sprites;
        TintList _tintList;

    public:
        Atlas(TexturePtr atlasTexture, const string &spritsJson);

        std::pair<bool, Rect> GetSprite(string const &name) const;
        bool WriteSprite(Renderer &, string const& name, const Rect& destRect) const;
        bool WriteSprite(Renderer &, string const &name, Vector2 const &topLeft) const;

        template <class ...Args>
        static shared_ptr<Atlas> Load(std::string const& baseName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            auto* renderer = std::get<1>(tuple);
            return LoadAtlas(resources, *renderer, baseName, id);
        }

    private:
        static shared_ptr<Atlas> LoadAtlas(ResourceManager &, Renderer &, string const& baseName, ResourceId const& id);
        bool WriteSprite(Renderer &, Rect const &sourceRect, Rect const &destRect) const;
        bool ReadSprites(const string &fileName);
    };
}
