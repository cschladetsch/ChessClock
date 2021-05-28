#pragma once

#include <unordered_map>

#include "ChessClock/Renderer.hpp"
#include "ChessClock/ResourceBase.hpp"

namespace ChessClock
{
    template <class Ty>
    class Resource : ResourceBase
    {
        const Ty& Get();
    };

    class ResourceManager
    {
        std::unordered_map<std::string, int> _nameToId;
        std::unordered_map<int, ResourceBase*> _idToResource;

    public:
        ResourceManager::ResourceManager(Renderer const &renderer, const char* rootDir)
        {
        }

        template <class Ty>
        Resource<Ty> GetResource(const char* name);

        template <class Ty>
        Resource<Ty> GetResource(int id);
    };

}
