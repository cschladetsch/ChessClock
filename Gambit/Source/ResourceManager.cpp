#include "Gambit/ResourceManager.hpp"

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

    ResourceId ResourceManager::NewId(string const &name) const
    {
        return ResourceId(name);
    }

    bool ResourceManager::AddObject(ObjectPtr obj)
    {
        _idToObject[obj->GetResourceId()] = obj;
        return true;
    }

    void ResourceManager::AddResource(ResourceId const& id, ResourceBasePtr resource)
    {
        _idToResource[id] = resource;
    }

    ObjectPtr ResourceManager::CreateObject(const string &name)
    {
        auto result = std::make_shared<Object>(name, NewId(name), *this);
        AddObject(result);
        return result;
    }

    ResourceBasePtr ResourceManager::GetResource(ResourceId const& id) const
    {
        auto found = _idToResource.find(id);
        if (found == _idToResource.end())
            return 0;
        return found->second;
    }

    ObjectPtr ResourceManager::FindObject(string const &name)
    {
        for (auto &iter : _idToObject)
        {
            if (iter.first.GetName() == name)
                return iter.second;
        }

        LOG_ERROR() << "Couldn't find object " << LOG_VALUE(name) << "\n";
        return 0;
    }
}

