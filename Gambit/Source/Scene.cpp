#include "Gambit/Scene.hpp"
#include "Gambit/ThirdParty/Json.hpp"

namespace Gambit
{
    void Scene::PreUpdate()
    {
    }

    void Scene::Update()
    {
    }

    void Scene::PostUpdate()
    {
    }

    void Scene::PreRender()
    {
    }

    void Scene::Render()
    {
    }

    void Scene::PostRender()
    {
    }

    shared_ptr<Scene> Scene::LoadScene(ResourceManager&, const char* fileName)
    {
        return 0;
    }
}
