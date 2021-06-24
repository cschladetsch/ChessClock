#include "Gambit/Atlas.hpp"
#include "Gambit/Scene.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/ThirdParty/Json.hpp"

// conversion 
#pragma warning (disable:4244)

namespace Gambit
{
    using namespace std;

    Scene::Scene(ResourceId const &id, ResourceManager &resourceManager, Atlas const &atlas, const char* fileName)
        : ResourceBase(id)
        , _resourceManager(&resourceManager)
        , _atlas(&atlas)
    {
        ReadJsonEx(fileName);
    }

    ObjectPtr Scene::FindChild(string const &name) const
    {
        return _resourceManager->FindObject(name);
    }

    ObjectPtr Scene::GetRoot(ObjectPtr object)
    {
        if (!object)
        {
            LOG_ERROR() << "null object";
            return 0;
        }
        int layer = object->Layer;
        auto root = _layerToRoots.find(layer);
        if (root != _layerToRoots.end())
        {
            return root->second;
        }

        std::stringstream out;
        out << "Root" << layer << std::ends;
        return _layerToRoots[layer] = make_shared<Object>(out.str(), _resourceManager->NewId(), *_resourceManager);
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

    bool logRender{ true };

    void Scene::Render(Renderer &renderer) const
    {
        for (auto& root : _layerToRoots)
        {
            for (auto& object : root.second->GetChildren())
            {
                if (!object->Sprite.empty())
                {
                    if (logRender)
                        LOG_DEBUG() << "Drawing " << LOG_VALUE(object->Name) << ", " << LOG_VALUE(object->Layer) << LOG_VALUE(object->Tint) << LOG_VALUE(object->Mirror) << "\n";

                    _atlas->WriteSprite(renderer, *object);
                }
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

    void Scene::AddObject(ObjectPtr object)
    {
        GetRoot(object)->AddChild(object);
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

        AddObject(objectPtr);

        return true;
    }
}

