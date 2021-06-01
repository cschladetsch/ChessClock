#include <exception>
#include <algorithm>

#include "Gambit/Transform.hpp"
#include "Gambit/Exceptions.hpp"

namespace Gambit
{
    void Transform::SetParent(TransformPtr parent)
    {
        auto ptr = shared_from_this();
        if (_parent)
        {
            if (!_parent->RemoveChild(ptr))
            {
                LOG_WARN() << "Attempt to remove child from parent failed.\n";
            }
        }
        _parent->AddChild(ptr);
    }

    Vector2 Transform::Apply(Vector2 const& point)
    {
        throw NotImplemented();
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

    bool Transform::RemoveChild(TransformPtr transform)
    {
        auto child = GetChildWithGuid(transform->GetGuid());
        if (child != _children.end())
        {
            _children.erase(child);
            return true;
        }

        return false;
    }

    void Transform::ResolveChildren(ResourceManager const&)
    {
    }

    bool Transform::HasChildWithGuid(Guid const& id)
    {
        return GetChildWithGuid(id) != _children.end();
    }

    Transform::Children::iterator Transform::GetChildWithGuid(Guid const &id)
    {
        for (auto child = _children.begin(); child != _children.end(); ++child)
        {
            if (child->first.GetGuid() == id)
            {
                return child;
            }
        }
        return _children.end();
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

