#pragma once

#include "Gambit/JsonReader.hpp"
#include "Gambit/ResourceBase.hpp"

namespace ChessClock
{
    class ThemeMeta
        : public Gambit::ResourceBase
        , Gambit::JsonReader<ThemeMeta>
    {
        static inline Gambit::Logger _log{ "ThemeMeta"};

        using string = Gambit::string;
        using FontPtr = Gambit::FontPtr;

        typedef std::unordered_map<string, Gambit::FontPtr> Fonts;

        Gambit::ResourceManager *_resourceManager;
        string _name;
        Fonts _fonts;

    public:
        ThemeMeta(Gambit::ResourceManager &resourceManager, string const &jsonFileName);
        ThemeMeta(ThemeMeta const &) = default;
        virtual ~ThemeMeta() = default;

        FontPtr GetFont(string const &name) const;
        string const &GetName() const { return _name; }

        template <class ...Args>
        static std::shared_ptr<ThemeMeta> Load(std::string const& jsonName, Gambit::ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            return LoadThemeMeta(*resources, jsonName, id);
        }

    protected:
        static std::shared_ptr<ThemeMeta> LoadThemeMeta(Gambit::ResourceManager &, string const& jsonName, Gambit::ResourceId const& id);

        bool ParseJson(JsonNext &next) override;
    };
}
