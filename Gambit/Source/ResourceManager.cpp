#include "Gambit/ResourceManager.hpp"
#include "Gambit/Object.hpp"

namespace Gambit
{
    ResourceManager::ResourceManager(Renderer const& renderer, const char* rootFolder)
    {
        _renderer = &renderer;
        _rootFolder = rootFolder;
    }

    std::string ResourceManager::MakeResourceFilename(const char* name)
    {
        return _rootFolder + name;
    }

    ResourceId ResourceManager::NewId() const
    {
        return ResourceId();
    }

    bool ResourceManager::AddResource(ResourceId const &id, ResourceBasePtr resource)
    {
        auto iter = _objectToResources.find(id.GetGuid());
        if (iter != _objectToResources.end())
        {
            LOG_WARN() << "Attempt to add resource with exisiting id " << id.GetGuid() << "\n";
            return false;
        }

        _objectToResources[id.GetGuid()] = { resource->GetGuid() };
        return true;
    }

    bool ResourceManager::AddResource(Object const& owner, ResourceBasePtr resource)
    {
        auto const &resourceId = owner.GetResourceId();
        auto iter = _objectToResources.find(resourceId.GetGuid());
        if (iter == _objectToResources.end())
        {
            _objectToResources[resourceId.GetGuid()] = { resource->GetGuid() };
            return true;
        }

        auto& set = iter->second;
        set.push_back(resource->GetGuid());
        return true;
    }
}

