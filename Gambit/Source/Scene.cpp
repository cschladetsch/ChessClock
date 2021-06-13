#include "Gambit/Atlas.hpp"
#include "Gambit/Scene.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/ThirdParty/Json.hpp"

namespace Gambit
{
    using namespace std;

#pragma warning (disable:4244)

    Scene::Scene(ResourceId const &id, ResourceManager &resourceManager, Atlas const &atlas, const char* fileName)
        : ResourceBase(id)
        , _resourceManager(&resourceManager)
        , _atlas(&atlas)
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

    void Scene::Render(Renderer &renderer) const
    {
        for (auto& object : _root->GetChildren())
        {
            if (!object->Sprite.empty())
            {
                _atlas->WriteSprite(renderer, *object);
                //_atlas->WriteSprite(renderer, object->Sprite, object->Position, object->Tint);
            }
        }
    }

    void Scene::PostRender()
    {
    }

    shared_ptr<Scene> Scene::LoadScene(ResourceManager &resources, string const &fileName, Atlas const &atlas)
    {
        return make_shared<Scene>(resources.NewId(), resources, atlas, fileName.c_str());
    }

    bool Scene::ParseJson(JsonNext& item)
    {
        auto &name = item.key();
        auto &value = item.value();

        ObjectPtr objectPtr = _resourceManager->CreateObject(name);
        Object &object = *objectPtr;

        if (value.contains("location"))
        {
            auto& location = value["location"];
            object.Position = Vector2(location[0], location[1]);
        }

        //CJS TODO: 
        //SetValue(value, "location", object, &Object::Position, [](nlohmann::json& j) { return Vector2{ j[0], j[1] }; });
        SetValue(value, "sprite", object, &Object::Sprite);
        SetValue(value, "layer", object, &Object::Layer);
        SetValue(value, "mirror", object, &Object::Mirror);
        SetValue(value, "tint", object, &Object::Tint);

        _root->AddChild(objectPtr);

        return false;
    }
}

