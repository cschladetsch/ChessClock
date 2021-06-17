#pragma once

#include <unordered_map>

#include "Gambit/Resource.hpp"
#include "Gambit/ResourceLoader.hpp"
#include "Gambit/NonCopyable.hpp"
#include "Gambit/Object.hpp"
#include "Gambit/Scene.hpp"

namespace Gambit
{
    class ResourceManager
        : NonCopyable
    {
        static inline Logger _log{ "ResourceManager" };

        typedef std::unordered_map<ResourceId, ResourceBasePtr> IdToResources;
        typedef std::unordered_map<ResourceId, ObjectPtr> IdToObject;

        IdToResources _idToResource;
        IdToObject _idToObject;

        Renderer const* _renderer;
        string _rootFolder;

    public:
        ResourceManager(Renderer const &renderer, const char *rootFolder);
        ResourceManager(ResourceManager &) = delete;

        bool AddObject(Object *obj)
        {
            _idToObject[obj->GetResourceId()] = std::make_shared<Object>(*obj);
            //LOG_VERBOSE() << this << LOG_VALUE(obj->GetResourceId().GetName()) << LOG_VALUE(obj) << LOG_VALUE(_idToObject.size()) << "\n";
            return true;
        }

        IdToObject const &GetObjects() const { return _idToObject; }

        ObjectPtr CreateObject(const string &name)
        {
            return std::make_shared<Object>(name, NewId(name), *this);
        }

        template <class Res, class ...Args>
        shared_ptr<Res> LoadResource(const char* name, Args... args)
        {
            ResourceId id{ xg::newGuid(), name };
            auto fileName = MakeResourceFilename(name);
            auto resource = ResourceLoader<Res>::Load(fileName, id, args...);
            if (!resource)
            {
                return 0;
            }
            _idToResource[id] = resource->SharedBase();
            return resource;
        }

        template <class Res, class ...Args>
        shared_ptr<Res> CreateResource(const char* name, Args... args)
        {
            ResourceId id{ xg::newGuid(), name };
            shared_ptr<Res> resource = std::make_shared<Res>(id, args...);
            if (!resource)
            {
                LOG_ERROR() << "Failed to make resource type `" << NAMEOF_TYPE(Res) << " from resource " << name << "\n";
                return 0;
            }
            _idToResource[id] = resource->SharedBase();
            return resource;
        }

        ResourceBasePtr GetResource(ResourceId const& id) const
        {
            auto found = _idToResource.find(id);
            if (found == _idToResource.end())
                return 0;
            return found->second;
        }

        void AddResource(ResourceId const& id, ResourceBasePtr resource)
        {
            _idToResource[id] = resource;
        }

        ResourceId NewId() const;
        ResourceId NewId(string const &name) const;

        string MakeResourceFilename(const char* name);

        ObjectPtr FindObject(string const &name);
    };
}
