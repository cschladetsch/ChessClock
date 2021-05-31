#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/Guid.hpp"
#include "Gambit/ResourceBase.hpp"
#include "Gambit/Vector2.hpp"

namespace Gambit
{
    class Transform
        : public ResourceBase
    {
        typedef std::vector<std::pair<ResourceId, TransformPtr>> Children;

        friend class ResourceManager;

        Children _children;
        TransformPtr _parent;
        Guid _guid;

    public:
        Vector2 position;
        float rotation;
        float scale;

        Children const& GetChildren() const { return _children; }
        TransformPtr GetParent() const { return _parent; }

        Transform(Vector2 const& pos, float rot, float _scale = 1)
            : position(pos), rotation(rot), scale(_scale)
        {
        }

        void SetParent(TransformPtr parent);
        Vector2 Apply(Vector2 const& point);

        bool AddChild(Guid id);
        bool AddChild(TransformPtr ptr);

    private:
        void ResolveChildren(ResourceManager const&);
        bool HasChildWithGuid(Guid const& id);
    };
}


