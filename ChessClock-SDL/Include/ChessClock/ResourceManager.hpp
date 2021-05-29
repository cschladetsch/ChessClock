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
        std::string _rootFolder;
        Renderer const* _renderer;
        Logger _log{ "ResourceManager" };

    public:
        ResourceManager(Renderer const& renderer, const char* rootFolder);

        template <class Ty>
        std::shared_ptr<Resource<Ty>> CreateResource(const char* name)
        {
            auto resource = ResourceLoader<Ty>::Load(_rootFolder, name);
            return 0;// std::make_shared(new Resource<T>;
        }

        template <class Ty>
        Resource<Ty> GetResource(ResourceId const&);
    };
}
