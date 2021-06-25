#pragma once

#include <map>

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Resource.hpp"
#include "Gambit/JsonReader.hpp"

namespace Gambit
{
    class Scene
        : public ResourceBase
        , JsonReader<Scene>
    {
        static inline Logger _log{ "Scene" };

        typedef std::map<int, ObjectPtr> LayerToRoot;

        ResourceManager* _resourceManager;
        Atlas const* _atlas;
        LayerToRoot _layerToRoots;

    public:
        Scene(ResourceId const &, ResourceManager&, Atlas const &, const char* fileName);

        template <class ...Args>
        static shared_ptr<Scene> Load(std::string const& fileName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            auto& atlas = std::get<1>(tuple);
            return LoadScene(*resources, fileName, *atlas);
        }

        ObjectPtr GetRoot(ObjectPtr object);
        void AddObject(ObjectPtr object);

        void PreUpdate();
        void Update();
        void PostUpdate();

        void PreRender();
        void Render(Renderer &renderer) const;
        void PostRender();

        ObjectPtr FindChild(string const &) const;

    private:
        static shared_ptr<Scene> LoadScene(ResourceManager &, string const &fileName, Atlas const &atlas);

        bool ParseJson(JsonNext &item);
    };
}
