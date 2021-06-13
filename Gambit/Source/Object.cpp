#include "Gambit/Object.hpp"
#include "Gambit/Exceptions.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    Object::Object(ResourceId const&resourceId, ResourceManager& resourceManager)
        : _resourceManager(&resourceManager)
        , ResourceBase(resourceId)
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
