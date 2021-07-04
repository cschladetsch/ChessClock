#include "Gambit/Font.hpp"
#include "Gambit/ResourceManager.hpp"

#include "ChessClock/ThemeMeta.hpp"

namespace ChessClock
{
    using namespace std;

    ThemeMeta::ThemeMeta(ResourceManager &rm, string const &jsonFileName)
        : _resourceManager(&rm)
    {
        ReadJsonEx(jsonFileName);
    }

    shared_ptr<ThemeMeta> ThemeMeta::LoadThemeMeta(ResourceManager &resources , string const& jsonName)
    {
        return make_shared<ThemeMeta>(resources, jsonName);
    }

    ThemeMeta::FontPtr ThemeMeta::GetFont(string const &name) const
    {
        auto const &found = _fonts.find(name);
        if (found == _fonts.end())
        {
            LOG_ERROR() << "FontName not found " << LOG_VALUE(name) << "\n;";
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
            map<string, vector<nlohmann::json>> fonts;
            value.get_to(fonts);
            for (auto & [first, second] : fonts)
            {
                string fontFileName = second.at(0);
                const int pointSize = second.at(1);

                _fonts[first] = _resourceManager->LoadResource<Gambit::Font>(fontFileName, pointSize);
            }

            return true;
        }

        return false;
    }
}

