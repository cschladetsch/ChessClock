#pragma once

#include "Gambit/JsonReader.hpp"
#include "Gambit/ResourceBase.hpp"

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    class ThemeMeta
        : public Gambit::ResourceBase
        , Gambit::JsonReader<ThemeMeta>
    {
        static inline Logger _log{ "ThemeMeta"};

        using string = Gambit::string;
        using FontPtr = Gambit::FontPtr;
        using ResourceManager = Gambit::ResourceManager;

        typedef std::unordered_map<string, FontPtr> Fonts;

        ResourceManager *_resourceManager;
        string _name;
        Fonts _fonts;

    public:
        ThemeMeta(ResourceManager &resourceManager, string const &jsonFileName);
        virtual ~ThemeMeta() = default;

        FontPtr GetFont(string const &name) const;
        string const &GetThemeName() const { return _name; }

        template <class ...Args>
        static SharedPtr<ThemeMeta> Load(std::string const& jsonName, Gambit::ResourceId const& id, Args... args)
        {
            auto *resources = std::get<0>(std::tuple{ args... });
            return LoadThemeMeta(*resources, jsonName);
        }

    private:
        static std::shared_ptr<ThemeMeta> LoadThemeMeta(ResourceManager &, string const &jsonName);

        bool ParseJson(JsonNext &item) override;
    };
}

