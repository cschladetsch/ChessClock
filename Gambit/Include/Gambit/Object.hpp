#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceBase.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/ForwardReferences.hpp"

namespace Gambit
{
    class Object
        : public std::enable_shared_from_this<Object>
    {
        static inline Logger _log{ "Object" };

        typedef std::vector<ObjectPtr> Children;
        typedef std::vector<ResourceBasePtr> Resources;

        ResourceManager* _resourceManager{ 0 };
        ResourceId _resourceId;
        Children _children;
        Resources _resources;
        ObjectPtr _parent;

    public:

        string Name;
        Vector2 Position;
        float Rotation{ 0 };
        float Scale{ 1 };
        string Sprite;
        int Layer{ 0 };
        bool Mirror{ false };
        string Tint;

        Object(string name, ResourceId const&, ResourceManager& resourceManager);

        Resources const& GetResources() const { return _resources; }
        bool HasResource(ResourceBasePtr) const;
        bool AddResource(ResourceBasePtr);
        void RemoveResource(ResourceBasePtr);
        ResourceBasePtr GetResource(Guid const &guid) const;

        Children const& GetChildren() const { return _children; }
        bool HasChild(ObjectPtr) const;
        bool AddChild(ObjectPtr);
        void RemoveChild(ObjectPtr);

        ObjectPtr GetParent();
        void SetParent(ObjectPtr);

        ResourceId const &GetResourceId() const { return _resourceId; }
    };
}
