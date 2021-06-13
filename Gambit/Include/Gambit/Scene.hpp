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
        TransformPtr _root;

    public:
        Scene(ResourceId const &, ResourceManager&, const char* fileName);

        template <class ...Args>
        static shared_ptr<Scene> Load(std::string const& fileName, ResourceId const& id, Args... args)
        {
            auto tuple = std::tuple{ args... };
            auto& resources = std::get<0>(tuple);
            return LoadScene(resources, fileName);
        }

        TransformPtr GetRoot() const { return _root; }

        void PreUpdate();
        void Update();
        void PostUpdate();

        void PreRender();
        void Render();
        void PostRender();

    private:
        static shared_ptr<Scene> LoadScene(ResourceManager &, string const &fileName);
        bool ParseJson(JsonNext &item);
    };
}
