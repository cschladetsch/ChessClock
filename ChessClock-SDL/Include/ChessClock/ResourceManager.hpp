#pragma once

#include <unordered_map>

#include "ChessClock/Renderer.hpp"
#include "ChessClock/Resource.hpp"
#include "ChessClock/ResourceLoader.hpp"

namespace ChessClock
{
    class ResourceManager
    {
        std::unordered_map<Guid, ResourceBase *> _guidToResource;
        string _rootFolder;
        Renderer const* _renderer;
        Logger _log{ "ResourceManager" };

    public:
        ResourceManager(Renderer const& renderer, const char* rootFolder);

        template <class Res, class ...Args>
        shared_ptr<Res> CreateResource(const char* name, Args... args)
        {
            ResourceId id{ xg::newGuid(), name };
            return ResourceLoader<Res>::Load(MakeFilename(name), id, args...);
        }

        ResourceId NewId() const;

        string MakeFilename(const char* name);

        template <class Ty>
        Resource<Ty> GetResource(ResourceId const&);
    };
}
