#pragma once

#include "Gambit/ResourceBase.hpp"
#include "Gambit/Resource.hpp"

namespace Gambit
{
    class Text : public Resource<string>
    {
    public:
        Text(ResourceId const&, const std::string const &);

        static shared_ptr<Text> Load(std::string const& fileName, ResourceId const& id);
    };
}
