#pragma once

#include <vector>

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/ResourceId.hpp"
#include "ChessClock/Logger.hpp"

namespace ChessClock
{
    class Object
    {
        typedef std::vector<ComponentPtr> Components;

        ResourceManager* _resourceManager{ 0 };
        ResourceId _resourceId;
        Logger _log;
       
    public:
        Object(ResourceId const &resourceId);

        Transform& GetTransform();
        Transform const& GetTransform() const;

        void AddComponent(ComponentPtr component);

        Components const& GetComponents() const;
        Component const& GetComponent(Guid const &guid) const;
    };
}
