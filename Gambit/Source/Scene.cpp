#include "Gambit/Atlas.hpp"
#include "Gambit/Scene.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/ThirdParty/Json.hpp"

// conversion 
#pragma warning (disable:4244)

namespace Gambit
{
    using namespace std;

    Scene::Scene(ResourceId const &id, ResourceManager &resourceManager, Atlas const &atlas, const char *fileName)
        : ResourceBase(id)
        , _resourceManager(&resourceManager)
        , _atlas(&atlas)
    {
        ReadJsonEx(fileName);

        LOG_INFO() << "Created scene: " << LOG_VALUE(fileName) << "\n";
    }

    ObjectPtr Scene::FindChild(string const &name) const
    {
        return _resourceManager->FindObject(name);
    }

    ObjectPtr Scene::OnPressed(AtlasPtr atlas, Vector2 where) const
    {
        for (auto const &button : _buttons)
        {
            auto pair = atlas->GetSprite(button->Sprite);
            if (!pair.first)
                continue;

            auto &atlasRect = pair.second;
            auto const &pos = button->Position;
            auto rect = Rect{ pos.y, pos.x, atlasRect.width, atlasRect.height };
            if (!rect.Contains(where))
                continue;

            return button;
        }

        return nullptr;
    }

    ObjectPtr Scene::GetLayer(ObjectPtr object)
    {
        if (!object)
        {
            LOG_ERROR() << "null object\n";
            return 0;
        }
        int layer = object->Layer;
        auto root = _layerToRoots.find(layer);
        if (root != _layerToRoots.end())
        {
            return root->second;
        }

        stringstream out;
        out << "Root" << layer << std::ends;
        return _layerToRoots[layer] = make_shared<Object>(out.str(), ResourceId(), *_resourceManager);
    }

    void Scene::Render(Renderer &renderer) const
    {
        for (auto& root : _layerToRoots)
        {
            for (auto& object : root.second->GetChildren())
            {
                if (object->Sprite.empty())
                    continue;

                _atlas->WriteSprite(renderer, *object);
            }
        }
    }

    shared_ptr<Scene> Scene::LoadScene(ResourceManager &resources, string const &fileName, Atlas const &atlas)
    {
        return make_shared<Scene>(ResourceId(), resources, atlas, fileName.c_str());
    }

    void Scene::AddObject(ObjectPtr object)
    {
        if (!object)
        {
            LOG_WARN() << "Attempt to add null object\n";
            return;
        }

        GetLayer(object)->AddChild(object);

        if (object->Type == "button")
        {
            _buttons.push_back(object);
        }
    }

    bool Scene::ParseJson(JsonNext& item)
    {
        auto &name = item.key();
        auto &value = item.value();

        ObjectPtr objectPtr = _resourceManager->CreateObject(name);
        Object &object = *objectPtr;

        //CJS TODO: why does this work if I make a variable to pass, rather than passing the lambda directly to SetValue(...)
        std::function<Vector2 (nlohmann::json &j)>fun = [](nlohmann::json& j) { return Vector2{ j[0], j[1] }; };
        //SetValue(value, "location", object, &Object::Position, [](nlohmann::json& j) { return Vector2{ j[0], j[1] }; });
        SetValue(value, "location", object, &Object::Position, fun);
        SetValue(value, "sprite", object, &Object::Sprite);
        SetValue(value, "layer", object, &Object::Layer);
        SetValue(value, "mirror", object, &Object::Mirror);
        SetValue(value, "tint", object, &Object::Tint);
        SetValue(value, "type", object, &Object::Type);
        SetValue(value, "callback", object, &Object::Callback);
        SetValue(value, "rotation", object, &Object::Rotation);

        AddObject(objectPtr);

        return true;
    }
}

