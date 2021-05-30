#pragma once

#include <unordered_map>

//#include "ChessClock/Renderer.hpp"
#include "ChessClock/Resource.hpp"
#include "ChessClock/ResourceLoader.hpp"

namespace ChessClock
{
    class ResourceManager
    {
        std::unordered_map<ResourceId, ResourceBase *> _idToResource;
        string _rootFolder;
        Renderer const* _renderer;
        Logger _log{ "ResourceManager" };

    public:
        ResourceManager(Renderer const& renderer, const char* rootFolder);

        template <class Res, class ...Args>
        shared_ptr<Res> CreateResource(const char* name, Args... args)
        {
            ResourceId id{ xg::newGuid(), name };
            auto resource = ResourceLoader<Res>::Load(MakeFilename(name), id, args...);
            //return _idToResource[id] = resource;
            return resource;
        }

        ResourceId NewId() const;

        string MakeFilename(const char* name);

        template <class Ty>
        Resource<Ty> GetResource(ResourceId const&);
    };
}
