#pragma once

#include "ChessClock/ResourceBase.hpp"
#include "ChessClock/ResourceLoader.hpp"

namespace ChessClock
{
    class Text : public ResourceBase
    {
        std::string _text;

    public:
        Text(std::string const &string, ResourceId const&);

        static std::shared_ptr<Text> Load(std::string const& root, std::string const& name);
    };

    template <>
    struct ResourceLoader<Text>
    {
        std::shared_ptr<Text> Load(std::string const& root, std::string const& name)
        {
            return Text::Load(root, name);
        }
    };
}
