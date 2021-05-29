#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "crossguid/guid.hpp"

#include "ChessClock/Config.hpp"
#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/Vector2.hpp"

namespace ChessClock
{
    class Transform
    {
        typedef std::vector<std::pair<ResourceId, ResourceBasePtr>> Children;

        friend class ResourceManager;

        Children _children;
        ResourceId _resourceId;

    public:
        Vector2 position;
        float rotation;
        float scale;

        ResourceId const& GetId() const { return _resourceId; }

        Transform(Vector2 const& pos, float rot, float _scale = 1)
            : position(pos), rotation(rot), scale(_scale)
        {
        }

        Vector2 Apply(Vector2 const& point);

        bool Add(ResourceBasePtr ptr)
        {
            AddChild(ptr);
        }

        void SetChildIs(std::vector<Guid> const& childrenIds)
        {
            for (auto id : childrenIds)
            {

            }
        }

        void ResolveChildren(ResourceManager const&);

    private:
        bool AddChild(ResourceBasePtr ptr)
        {
            for (auto &child : _children)
            {
                if (child.first.GetGuid() == ptr->GetGuid())
                    return false;
            }
            
            _children.push_back(std::make_pair(ptr->GetGuid(), ptr));
            return true;
        }
    };
}


