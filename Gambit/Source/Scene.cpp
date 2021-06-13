#include "Gambit/Scene.hpp"
#include "Gambit/Transform.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/ThirdParty/Json.hpp"

namespace Gambit
{
    using namespace std;

#pragma warning (disable:4244)

    Scene::Scene(ResourceId const &id, ResourceManager &resourceManager, const char* fileName)
        : ResourceBase(id)
        , _resourceManager(&resourceManager)
    {
        _root = make_shared<Object>("root", resourceManager.NewId(), resourceManager);

        if (!ReadJson(fileName))
        {
            LOG_ERROR() << "Failed to load scene from " << LOG_VALUE(fileName) << "\n";
            return;
        }
    }

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

    shared_ptr<Scene> Scene::LoadScene(ResourceManager &resources, string const &fileName)
    {
        return make_shared<Scene>(resources.NewId(), resources, fileName.c_str());
    }

    bool Scene::ParseJson(JsonNext& item)
    {
        auto& name = item.key();
        auto& value = item.value();
        auto const& id = _resourceManager->NewId();
        ObjectPtr object = std::make_shared<Object>(name.c_str(), id, *_resourceManager);

        auto& sprite = value["sprite"];
        auto& location = value["location"];
        auto& layer = value["layer"];

        object->Sprite = sprite;
        object->Position = Vector2(location[0], location[1]);

        if (value.contains("mirror"))
        {
            object->Mirror = value["mirror"];
        }
        if (value.contains("tint"))
        {
            object->Tint = value["tint"];
        }

        _root->AddChild(object);

        return false;
    }
}
