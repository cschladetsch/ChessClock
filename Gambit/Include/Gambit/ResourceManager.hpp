#pragma once

#include <unordered_map>
#include <boost/filesystem.hpp>

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
        boost::filesystem::path _rootFolder;

    public:
        ResourceManager(Renderer const &renderer, const char *rootFolder);

        bool AddObject(ObjectPtr const &object);
        ObjectPtr CreateObject(const string &name);
        IdToObject const &GetObjects() const { return _idToObject; }

        template <class Res, class ...Args>
        shared_ptr<Res> LoadResource(string const &name, Args... args)
        {
            ResourceId id{ xg::newGuid(), name };
            auto fileName = MakeResourceFilename(name);
            auto resource = ResourceLoader<Res>::Load(fileName, id, args...);
            if (!resource)
            {
                LOG_ERROR() << "Failed to load resource '" << name << "'\n";
                return nullptr;
            }
            return AddResource(id, resource->SharedBase()), resource;
        }

        template <class Res, class ...Args>
        shared_ptr<Res> CreateResource(string const &name, Args... args)
        {
            ResourceId id{ xg::newGuid(), name };
            shared_ptr<Res> resource = std::make_shared<Res>(id, args...);
            if (!resource)
            {
                LOG_ERROR() << "Failed to make resource type '" << NAMEOF_TYPE(Res) << "' from resource " << name << "'\n";
                return nullptr;
            }
            return AddResource(id, resource->SharedBase()), resource;
        }

        ResourceBasePtr AddResource(ResourceId const &id, ResourceBasePtr resource);
        ResourceBasePtr GetResource(ResourceId const &id) const;
        string MakeResourceFilename(string const &name) const;
        ObjectPtr FindObject(string const &name) const;

        IdToObject const &GetAllObjects() const { return _idToObject; }
    };
}

