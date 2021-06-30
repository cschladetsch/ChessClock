#include "Gambit/ResourceManager.hpp"

namespace Gambit
{
    ResourceManager::ResourceManager(Renderer const& renderer, const char* rootFolder)
    {
        _renderer = &renderer;
        _rootFolder = rootFolder;
    }

    std::string ResourceManager::MakeResourceFilename(string const &name) const
    {
        return _rootFolder + name;
    }

    bool ResourceManager::AddObject(ObjectPtr const &object)
    {
        auto const &rid = object->GetResourceId();
        if (_idToObject.find(rid) != _idToObject.end())
        {
            LOG_ERROR() << "Attempt to store object with same id '" << rid << "' to resource manager.\n";
            return false;
        }
        _idToObject[rid] = object;
        return true;
    }

    void ResourceManager::AddResource(ResourceId const& id, ResourceBasePtr resource)
    {
        if (_idToResource.find(id) != _idToResource.end())
        {
            LOG_ERROR() << "Attempt to add resource id '" << id << "' to resource manager.\n";
            return;
        }

        _idToResource[id] = std::move(resource);
    }

    ObjectPtr ResourceManager::CreateObject(const string &name)
    {
        const auto result = std::make_shared<Object>(name, ResourceId(name), *this);
        return AddObject(result) ? result : nullptr;
    }

    ResourceBasePtr ResourceManager::GetResource(ResourceId const& id) const
    {
        const auto found = _idToResource.find(id);
        return found == _idToResource.end() ? nullptr : found->second;
    }

    ObjectPtr ResourceManager::FindObject(string const &name) const
    {
        for (const auto & [first, second] : _idToObject)
        {
            if (first.GetName() == name)
                return second;
        }

        LOG_ERROR() << "Couldn't find object " << LOG_VALUE(name) << "\n";

        return nullptr;
    }
}

