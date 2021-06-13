#include "Gambit/Object.hpp"
#include "Gambit/Transform.hpp"
#include "Gambit/Exceptions.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    Object::Object(string name, ResourceId const&resourceId, ResourceManager& resourceManager)
        : Name(name), _resourceId(resourceId), _resourceManager(&resourceManager)
    {
    }

    bool Object::HasResource(ResourceBasePtr resource) const
    {
        return std::find(_resources.begin(), _resources.end(), resource) != _resources.end();
    }

    bool Object::AddResource(ResourceBasePtr resource)
    {
        if (HasResource(resource))
            return false;

        _resources.push_back(resource);
        return true;
    }

    bool Object::HasChild(ObjectPtr object) const
    {
        return std::find(_children.begin(), _children.end(), object) != _children.end();
    }

    void Object::RemoveResource(ResourceBasePtr resource)
    {
        auto found = find(_resources.begin(), _resources.end(), resource);
        if (found != _resources.end())
            _resources.erase(found);
    }

    bool Object::AddChild(ObjectPtr object)
    {
        auto found = find(_children.begin(), _children.end(), object);
        if (found == _children.end())
        {
            _children.push_back(object);
            return true;
        }

        return false;
    }

    void Object::RemoveChild(ObjectPtr object)
    {
        auto found = find(_children.begin(), _children.end(), object);
        if (found != _children.end())
            _children.erase(found);
    }

    ObjectPtr Object::GetParent()
    {
        return _parent;
    }

    void Object::SetParent(ObjectPtr parent)
    {
        if (_parent)
            _parent->RemoveChild(shared_from_this());

        parent->AddChild(shared_from_this());
    }
}
