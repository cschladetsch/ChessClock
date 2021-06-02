#pragma once

#include <set>
#include <unordered_map>

#include "Gambit/Resource.hpp"
#include "Gambit/ResourceLoader.hpp"
#include "Gambit/Object.hpp"

namespace Gambit
{
    class ResourceManager
    {
        static inline Logger _log{ "ResourceManager" };
        typedef std::unordered_map<ResourceId, ResourceBasePtr> Resources;
        typedef std::unordered_map<ResourceId, ComponentPtr> Components;
        typedef std::unordered_map<ResourceId, std::set<ComponentPtr>> ObjectToComponents;

        Resources _idToResource;
        Components _idToComponents;
        ObjectToComponents _objectToComponents;
        Renderer const* _renderer;
        string _rootFolder;

    public:
        ResourceManager(Renderer const &renderer, const char *rootFolder);

        template <class Res, class ...Args>
        shared_ptr<Res> CreateResource(const char* name, Args... args)
        {
            ResourceId id{ xg::newGuid(), name };
            auto resource = ResourceLoader<Res>::Load(MakeResourceFilename(name), id, args...);
            _idToResource[id] = resource;
            return resource;
        }

        ResourceId NewId() const;

        string MakeResourceFilename(const char* name);

        bool AddComponent(Object const&, ComponentPtr);

        std::set<ComponentPtr> const &GetComponets(Object const&);


		/*
        template <class Ty>
        std::vector<ComponentPtr> GetComponents(Object const& object) const
        {
            auto found = _objectToComponents.find(object.GetResourceId());
            if (found == _objectToComponents.end())
            {
                return std::vector<ComponentPtr>();
            }
            std::vector<ComponentPtr> results;
            for (auto component : *found)
            {
                if (Ty* value = dynamic_cast<Ty>(&*component))
                {
                    results.push_back(value);
                }
            }
            return results;
        }
	*/

	/*
        template <class Ty>
        Resource<Ty> *GetResource(ResourceId const&rid)
        {
            auto found = _idToResource(rid);
            if (found == _idToResource.end())
            {
                return 0;
            }

            return dynamic_cast<Resource<Ty> *>(found->second);
        }
	*/
    };
}
