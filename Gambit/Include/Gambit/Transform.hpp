#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/Guid.hpp"
#include "Gambit/ResourceBase.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/Logger.hpp"

namespace Gambit
{
    class Transform
        : public ResourceBase
        , public std::enable_shared_from_this<Transform> 
    {
        typedef std::vector<std::pair<ResourceId, TransformPtr>> Children;

        friend class ResourceManager;

        Children _children;
        TransformPtr _parent;
        Guid _guid;
        Logger _log{ "Transform" };

        friend class Object;

        Transform(Vector2 const& pos = { 0,0 }, float rot = 0, float _scale = 1)
            : position(pos), rotation(rot), scale(_scale)
        {
        }

        std::shared_ptr<Transform> SharedTransform() { return std::enable_shared_from_this<Transform>::shared_from_this(); }

    public:
        Vector2 position;
        float rotation;
        float scale;

        Children const& GetChildren() const { return _children; }
        TransformPtr GetParent() const { return _parent; }

        void SetParent(TransformPtr parent);

        Vector2 Apply(Vector2 const& point);

        bool AddChild(Guid id);
        bool AddChild(TransformPtr transform);
        bool RemoveChild(TransformPtr transform);

    private:
        void ResolveChildren(ResourceManager const&);
        bool HasChildWithGuid(Guid const& id);
        Children::iterator GetChildWithGuid(Guid const& id);
    };
}


