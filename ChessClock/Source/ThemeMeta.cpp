#include "Gambit/Font.hpp"
#include "Gambit/ResourceManager.hpp"

#include "ChessClock/ThemeMeta.hpp"

namespace ChessClock
{
    ThemeMeta::ThemeMeta(Gambit::ResourceManager &rm, string const &jsonFileName)
        : _resourceManager(&rm)
    {
        ReadJsonEx(jsonFileName.c_str());
    }

    std::shared_ptr<ThemeMeta> ThemeMeta::LoadThemeMeta(Gambit::ResourceManager &resources , string const& jsonName, Gambit::ResourceId const& id)
    {
        return std::make_shared<ThemeMeta>(resources, jsonName.c_str());
    }

    ThemeMeta::FontPtr ThemeMeta::GetFont(string const &name) const
    {
        auto const &found = _fonts.find(name);
        if (found == _fonts.end())
        {
            LOG_ERROR() << "Font not found " << LOG_VALUE(name) << "\n;";
            return nullptr;
        }
        return found->second;
    }

    bool ThemeMeta::ParseJson(JsonNext &item)
    {
        auto &name = item.key();
        auto &value = item.value();

        if (name == "name")
        {
            _name = value;
            return true;
        }

        if (name == "fonts")
        {
            std::map<string, std::vector<nlohmann::json>> fonts;
            value.get_to(fonts);
            for (auto & [first, second] : fonts)
            {
                string tagName = first;
                string fontFileName = second.at(0);
                const int pointSize = second.at(1);

                _fonts[tagName] = _resourceManager->LoadResource<Gambit::Font>(fontFileName.c_str(), pointSize);
            }
        }

        return true;
    }
    
}
