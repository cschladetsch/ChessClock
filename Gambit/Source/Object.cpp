#include "Gambit/Object.hpp"
#include "Gambit/Exceptions.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    Object::Object(ResourceManager &rm, ResourceId const& resourceId)
        : _resourceManager(&rm), _resourceId(resourceId)
    {
    }

    void Object::AddComponent(ComponentPtr component)
    {
        _resourceManager->AddComponent(*this, component);
    }

    Object::Components const& Object::GetComponents() const
    {
        GAMBIT_NOT_IMPLEMENTED();
    }

    Component const& Object::GetComponent(Guid const& guid) const
    {
        GAMBIT_NOT_IMPLEMENTED();
    }
}
