#pragma once

#include <unordered_map>

//#include "Gambit/Renderer.hpp"
#include "Gambit/Resource.hpp"
#include "Gambit/ResourceLoader.hpp"

namespace Gambit
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
            _idToResource[id] = &*resource;
            return resource;
        }

        ResourceId NewId() const;

        string MakeFilename(const char* name);

        template <class Ty>
        Resource<Ty> GetResource(ResourceId const&);
    };
}
