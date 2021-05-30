#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "ChessClock/Config.hpp"
#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/ThirdParty/Guid.hpp"
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
        Children const& GetChildren() const { return _children; }

        Transform(Vector2 const& pos, float rot, float _scale = 1)
            : position(pos), rotation(rot), scale(_scale)
        {
        }

        Vector2 Apply(Vector2 const& point);

        bool Add(Guid id)
        {
            if (HasChildWithGuid(id))
            {
                return false;
            }

            _children.push_back(std::make_pair(ResourceId{ id }, ResourceBasePtr{}));
            return true;
        }

        bool Add(ResourceBasePtr ptr)
        {
            return AddChild(ptr);
        }

        void ResolveChildren(ResourceManager const&);

    private:
        bool HasChildWithGuid(Guid const &id)
        {
            for (auto& child : _children)
            {
                if (child.first.GetGuid() == id)
                {
                    return false;
                }
            }
            return true;
        }

        bool AddChild(ResourceBasePtr ptr)
        {
            if (HasChildWithGuid(ptr->GetGuid()))
            {
                return false;;
            }

            _children.push_back(std::make_pair(ptr->GetGuid(), ptr));
            return true;
        }
    };
}


