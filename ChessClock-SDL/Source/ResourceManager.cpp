#include "ChessClock/ResourceManager.hpp"

namespace ChessClock
{
    ResourceManager::ResourceManager(Renderer const& renderer, const char* rootFolder)
    {
        _renderer = &renderer;
        _rootFolder = rootFolder;
    }
}

