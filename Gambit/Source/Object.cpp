#include "Gambit/Object.hpp"
#include "Gambit/Exceptions.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    Object::Object(ResourceManager& rm, ResourceId const& resourceId)
        : _resourceManager(&rm), _resourceId(resourceId)
    {
    }

    void Object::AddResource(ResourceBasePtr resource)
    {
    }

    Object::Resources Object::GetResources() const
    {
        GAMBIT_NOT_IMPLEMENTED();
    }

    ResourceBasePtr Object::GetResource(Guid const& guid) const
    {
        GAMBIT_NOT_IMPLEMENTED();
    }
}
