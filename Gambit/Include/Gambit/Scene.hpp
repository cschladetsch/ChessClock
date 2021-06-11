#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Resource.hpp"

namespace Gambit
{
    class Scene
        : Resource<Scene>
    {
        TransformPtr _root;
        typedef std::unordered_map<string, Object> Objects;

        Objects _objects;

    public:
        Scene();

        template <class ...Args>
        shared_ptr<Scene> Load(const char* fileName, Args ...args)
        {
            auto tuple = std::tuple{ args... };
            ResourceManager const *rm = std::get<0>(tuple);
            return LoadScene(rm, fileName);
        }

        TransformPtr GetRoot() const { return _root; }

        void PreUpdate();
        void Update();
        void PostUpdate();

        void PreRender();
        void Render();
        void PostRender();

    private:
        shared_ptr<Scene> LoadScene(ResourceManager &, const char* fileName);
    };
}
