#include "Gambit/ResourceManager.hpp"

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
}

