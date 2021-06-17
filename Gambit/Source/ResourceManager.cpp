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

