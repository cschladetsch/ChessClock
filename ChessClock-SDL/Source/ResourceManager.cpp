#include "Gambit/ResourceManager.hpp"
#include "Gambit/Object.hpp"
#include "Gambit/Component.hpp"

namespace Gambit
{
    ResourceManager::ResourceManager(Renderer const& renderer, const char* rootFolder)
    {
        _renderer = &renderer;
        _rootFolder = rootFolder;
    }

    std::string ResourceManager::MakeFilename(const char* name)
    {
        return _rootFolder + name;
    }

    ResourceId ResourceManager::NewId() const
    {
        return ResourceId();
    }

    std::set<ComponentPtr> ResourceManager::GetComponets(Object const& object)
    {
        auto iter = _objectToComponents.find(object.GetResourceId());
        if (iter == _objectToComponents.end())
            return std::set<ComponentPtr>();
        return iter->second;
    }

    bool ResourceManager::AddComponent(Object const& owner, ComponentPtr component)
    {
        auto const &resourceId = owner.GetResourceId();
        auto iter = _objectToComponents.find(resourceId);
        if (iter == _objectToComponents.end())
        {
            _objectToComponents[resourceId] = { component };
            return true;
        }

        auto& set = iter->second;
        auto exists = set.find(component);
        if (exists == set.end())
        {
            set.insert(component);
            return true;
        }

        return false;
    }
}

