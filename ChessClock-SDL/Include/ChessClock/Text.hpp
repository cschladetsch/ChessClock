#pragma once

#include "ChessClock/ResourceBase.hpp"
#include "ChessClock/Resource.hpp"

namespace ChessClock
{
    class Text : public Resource<string>
    {
    public:
        Text(ResourceId const&, const std::string const &);

        static shared_ptr<Text> Load(std::string const& fileName, ResourceId const& id);
    };
}
