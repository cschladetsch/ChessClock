#include "Gambit/Atlas.hpp"
#include "Gambit/Scene.hpp"

#include "Gambit/Renderer.hpp"
#include "Gambit/ResourceManager.hpp"
#include "Gambit/Texture.hpp"
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

    ObjectPtr Scene::OnPressed(AtlasPtr const &atlas, const Vector2 where) const
    {
        for (auto const &button : _buttons)
        {
            auto [found, rect] = atlas->GetSprite(button->Sprite);
            if (!found)
                continue;

            auto &atlasRect = rect;
            auto const &pos = button->Position;
            if (auto spriteRect = Rect{ pos.y, pos.x, atlasRect.width, atlasRect.height }; !spriteRect.Contains(where))
                continue;

            return button;
        }

        return nullptr;
    }

    ObjectPtr Scene::GetLayer(const ObjectPtr &object)
    {
        if (!object)
        {
            LOG_ERROR() << "null object\n";
            return nullptr;
        }

        const int layer = object->Layer;
        if (const auto &root = _layerToRoots.find(layer); root != _layerToRoots.end())
        {
            return root->second;
        }

        stringstream out;
        out << "Root #" << layer << std::ends;
        return _layerToRoots[layer] = make_shared<Object>(out.str(), ResourceId(), *_resourceManager);
    }

    void Scene::Render(Renderer &renderer) const
    {
        for (const auto& [first, second] : _layerToRoots)
        {
            for (auto& object : second->GetChildren())
            {
                auto position = object->Position;
                if (object->Centered)
                {
                    if (object->TextTexturePtr)
                    {
                        const auto bounds = object->TextTexturePtr->GetBounds();
                        position.x -= bounds.width / 2;
                        position.y -= bounds.height / 2;
                    }
                }
                if (object->TextTexturePtr)
                {
                    if (!renderer.WriteTexture(object->TextTexturePtr, position))
                    {
                        LOG_WARN() << "Failed to render " << object->Name << "\n";
                        //_resourceManager->RemoveResource(object);
                    }
                    continue;
                }

                if (object->Sprite.empty())
                    continue;

                _atlas->WriteSprite(renderer, position, *object);
            }
        }
    }

    shared_ptr<Scene> Scene::LoadScene(ResourceManager &resources, string const &fileName, Atlas const &atlas)
    {
        return make_shared<Scene>(ResourceId(), resources, atlas, fileName.c_str());
    }

    void Scene::AddObject(ObjectPtr const &object)
    {
        if (!object)
        {
            LOG_WARN() << "Attempt to add null object\n";
            return;
        }

        GetLayer(object)->AddChild(object);

        if (object->ObjectType == EObjectType::Button)
        {
            _buttons.push_back(object);
        }
    }

    bool Scene::ParseJson(JsonNext& item)
    {
        auto &name = item.key();
        auto &value = item.value();

        const ObjectPtr objectPtr = _resourceManager->CreateObject(name);
        Object &object = *objectPtr;

        //CJS TODO: why does this work if I make a variable to pass, rather than passing the lambda directly to SetValue(...)
        std::function<Vector2 (nlohmann::json &j)>fun = [](nlohmann::json& j) { return Vector2{ j[0], j[1] }; };
        //SetValue(value, "location", object, &Object::Position, [](nlohmann::json& j) { return Vector2{ j[0], j[1] }; });
        SetValue(value, "type", object, &Object::Type);
        SetValue(value, "font", object, &Object::FontName);
        SetValue(value, "location", object, &Object::Position, fun);
        SetValue(value, "sprite", object, &Object::Sprite);
        SetValue(value, "layer", object, &Object::Layer);
        SetValue(value, "mirror", object, &Object::Mirror);
        SetValue(value, "tint", object, &Object::Tint);
        SetValue(value, "type", object, &Object::Type);
        SetValue(value, "callback", object, &Object::Callback);
        SetValue(value, "rotation", object, &Object::Rotation);
        SetValue(value, "centered", object, &Object::Centered);
        SetValue(value, "hidden", object, &Object::Hidden);
        SetValue(value, "string", object, &Object::String);

        object.ObjectType = EObjectType::Sprite;
        if (object.Type == "text")
        {
            object.ObjectType = EObjectType::Text;
        }
        else if (object.Type == "timer_value")
        {
            object.ObjectType = EObjectType::TimerValue;
        }
        else if (object.Type == "timer_seconds")
        {
            object.ObjectType = EObjectType::SecondsValue;
        }
        else if (object.Type == "button")
        {
            object.ObjectType = EObjectType::Button;
        }

        AddObject(objectPtr);

        return true;
    }
}

