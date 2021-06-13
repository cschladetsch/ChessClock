#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Resource.hpp"
#include "Gambit/JsonReader.hpp"

namespace Gambit
{
    class Scene
        : public ResourceBase
        , JsonReader
    {
        static inline Logger _log{ "Scene" };

        typedef std::unordered_map<string, Object> Objects;

        ResourceManager* _resourceManager;
        Atlas const* _atlas;
        ObjectPtr _root;

    public:
        Scene(ResourceId const &, ResourceManager&, Atlas const &, const char* fileName);

        template <class ...Args>
        static shared_ptr<Scene> Load(std::string const& fileName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            auto& atlas = std::get<1>(tuple);
            return LoadScene(resources, fileName, *atlas);
        }

        ObjectPtr GetRoot() const { return _root; }

        void PreUpdate();
        void Update();
        void PostUpdate();

        void PreRender();
        void Render(Renderer &renderer);
        void PostRender();

    private:
        static shared_ptr<Scene> LoadScene(ResourceManager &, string const &fileName, Atlas const &atlas);

        template <class Ty>
        bool SetValue(nlohmann::json& item, const string &name, Object &object, Ty (Object::* member), std::function<Ty (nlohmann::json &j)> convert = nullptr)
        {
            if (!item.contains(name))
                return false;

            if (convert)
                (object.*member) = convert(item[name]);
            else
                (object.*member) = item[name];
            return true;
        }

        bool ParseJson(JsonNext &item);
    };
}
