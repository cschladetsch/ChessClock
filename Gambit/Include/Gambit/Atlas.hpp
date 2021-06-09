#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/Rect.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    class Atlas
        : public ResourceBase
    {
        static inline Logger _log{ "Atlas" };

        typedef std::unordered_map<string, Rect> Sprites;

        TexturePtr _atlasTexture;;
        Sprites _sprites;

    public:
        Atlas(TexturePtr atlasTexture, const string &spritsJson);

        bool WriteSprite(Renderer &, string const& name, TexturePtr texture, const Rect &destRect) const;

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
        bool ReadSprites(const string &fileName);
    };
}
