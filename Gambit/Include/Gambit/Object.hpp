#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceBase.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/ForwardReferences.hpp"
#include "Gambit/NonCopyable.hpp"

namespace Gambit
{
    enum class EObjectType
    {
        None,
        Sprite,
        Button,
        Text,
        TimerValue,
        SecondsValue,
    };

    class Object
        : public std::enable_shared_from_this<Object>
        , public NonCopyable
    {
        static inline Logger _log{ "Object" };

        typedef std::vector<ObjectPtr> Children;
        typedef std::vector<ResourceBasePtr> Resources;

        ResourceManager* _resourceManager{ nullptr };
        ResourceId _resourceId;
        Children _children;
        Resources _resources;
        ObjectPtr _parent;

    public:
        string Name;
        string Sprite;
        string Tint;
        string Type;
        string FontName;
        string Callback;
        Vector2 Position;
        double Rotation{ 0 };
        float Scale{ 1 };
        int Layer{ 0 };
        bool Mirror{ false };
        bool Centered{ false };
        bool Hidden{ false };
        EObjectType ObjectType{ EObjectType::None };
        string String;
        FontPtr Font;
        TexturePtr TextTexturePtr;

        Object(string name, ResourceId const&, ResourceManager& resourceManager);

        string const &GetName() const { return _resourceId.GetName(); }
        ResourceId const &GetResourceId() const { return _resourceId; }
        ResourceBasePtr GetResource(Guid const &guid) const;
        Children const& GetChildren() const { return _children; }
        Resources const& GetResources() const { return _resources; }
        ObjectPtr GetParent() const;

        bool HasResource(ResourceBasePtr const &) const;
        bool AddResource(ResourceBasePtr const &);
        void RemoveResource(ResourceBasePtr const &);
        bool HasChild(ObjectPtr const &) const;
        bool AddChild(ObjectPtr const &);
        void RemoveChild(ObjectPtr const &);
        void SetParent(ObjectPtr const &);
    };
}

