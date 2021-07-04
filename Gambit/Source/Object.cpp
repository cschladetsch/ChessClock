#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    using namespace std::ranges;

    Object::Object(string name, ResourceId const&resourceId, ResourceManager& resourceManager)
        : _resourceManager(&resourceManager), _resourceId(resourceId), Name(name)
    {
    }

    bool Object::HasResource(const ResourceBasePtr &resource) const
    {
        return find(_resources, resource) != _resources.end();
    }

    bool Object::AddResource(const ResourceBasePtr &resource)
    {
        if (HasResource(resource))
            return false;

        _resources.push_back(resource);
        return true;
    }

    bool Object::HasChild(ObjectPtr const &object) const
    {
        return find(_children, object) != _children.end();
    }

    void Object::RemoveResource(ResourceBasePtr const &resource)
    {
        if (const auto found = find(_resources.begin(), _resources.end(), resource); found != _resources.end())
            _resources.erase(found);
    }

    ResourceBasePtr Object::GetResource(Guid const& guid) const
    {
        for (auto &resource : _resources)
        {
            if (resource->GetGuid() == guid)
                return resource;
        }
        return nullptr;
    }

    bool Object::AddChild(ObjectPtr const &object)
    {
        if (const auto found = find(_children, object); found == _children.end())
        {
            _children.push_back(object);
            return true;
        }

        return false;
    }

    void Object::RemoveChild(ObjectPtr const &object)
    {
        if (const auto found = find(_children, object); found != _children.end())
            _children.erase(found);
    }

    ObjectPtr Object::GetParent() const
    {
        return _parent;
    }

    void Object::SetParent(ObjectPtr const &parent)
    {
        if (_parent)
            _parent->RemoveChild(shared_from_this());

        parent->AddChild(shared_from_this());
    }
}

