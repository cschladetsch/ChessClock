#pragma once

#include "ChessClock/ResourceBase.hpp"
#include "ChessClock/ResourceLoader.hpp"

namespace ChessClock
{
    class Text : public ResourceBase
    {
        std::string _text;

    public:
        Text(ResourceId const&, std::string const& string);

        static std::shared_ptr<Text> Load(std::string const& fileName, ResourceId const& id);
    };

    template <>
    struct ResourceLoader<Text>
    {
        std::shared_ptr<Text> Load(std::string const& fileName, ResourceId const &id)
        {
            return Text::Load(fileName, id);
        }
    };
}
