#include "Gambit/Transform.hpp"

namespace Gambit
{
    void Transform::SetParent(TransformPtr parent)
    {
    }

    Vector2 Transform::Apply(Vector2 const& point)
    {
        throw std::exception("not implemented");
    }

    bool Transform::AddChild(Guid id)
    {
        if (HasChildWithGuid(id))
        {
            return false;
        }

        _children.push_back(std::make_pair(ResourceId{ id }, TransformPtr{}));
        return true;
    }

    void Transform::ResolveChildren(ResourceManager const&)
    {
    }

    bool Transform::HasChildWithGuid(Guid const &id)
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

    bool Transform::AddChild(TransformPtr ptr)
    {
        if (HasChildWithGuid(ptr->GetGuid()))
        {
            return false;;
        }

        _children.push_back(std::make_pair(ptr->GetGuid(), ptr));
        return true;
    }
}

