#include "Gambit/Scene.hpp"
#include "Gambit/Transform.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/ThirdParty/Json.hpp"

namespace Gambit
{
    using namespace std;

    Scene::Scene(ResourceId const &id, ResourceManager &resourceManager, const char* fileName)
        : ResourceBase(id)
        , _resourceManager(&resourceManager)
    {
        if (!ReadJson(fileName))
        {
            LOG_ERROR() << "Failed to load scene from " << LOG_VALUE(fileName) << "\n";
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
        /*
		"sprite" : "background",
		"location" : [ 0, 0 ],
		"layer" : 0
		optional "mirror" : true
		optional "tint" : "button_pressed"
        */
        auto& name = item.key();
        auto& value = item.value();
        auto const& id = _resourceManager->NewId();
        ObjectPtr object = _resourceManager->CreateResource<Object>(name.c_str(), *_resourceManager);

        auto& sprite = value["sprite"];
        auto& location = value["location"];
        auto& layer = value["layer"];

        object->Sprite = sprite;
        //object->GetTransform()->position = 

        if (value.contains("mirror"))
        {

        }
        if (value.contains("tint"))
        {

        }

        return false;
    }
}
