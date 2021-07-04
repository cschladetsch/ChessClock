#pragma once

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

        typedef std::function<void(Object const &)> Callback;
        typedef std::unordered_map<string, Callback> Callbacks;
        typedef std::unordered_map<int, ObjectPtr> LayerToRoot;
        typedef std::vector<ObjectPtr> Buttons;

        ResourceManager* _resourceManager;
        Atlas const* _atlas;
        LayerToRoot _layerToRoots;
        Callbacks _buttonCallbacks;
        Buttons _buttons;

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

        ObjectPtr GetLayer(ObjectPtr object);
        void AddObject(ObjectPtr object);

        void Render(Renderer &renderer) const;

        ObjectPtr FindChild(string const &name) const;
        ObjectPtr OnPressed(AtlasPtr atlas, Vector2 where) const;

    private:
        static shared_ptr<Scene> LoadScene(ResourceManager &, string const &fileName, Atlas const &atlas);

        bool ParseJson(JsonNext &item) override;
    };
}

