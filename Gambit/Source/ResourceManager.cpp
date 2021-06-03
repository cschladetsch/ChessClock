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

    std::vector<ResourceBasePtr> ResourceManager::GetResources(Object const& object)
    {
        auto const &resourceId = object.GetResourceId();
        auto iter = _objectToResources.find(resourceId.GetGuid());
        if (iter == _objectToResources.end())
        {
            return std::move(std::vector<ResourceBasePtr>());
        }
        std::vector<ResourceBasePtr> result;
        for (auto const& resource: _objectToResources[object.GetResourceId().GetGuid()])
        {
            //result.push_back(_idToResource[guid]);
        }
        return std::move(result);
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

