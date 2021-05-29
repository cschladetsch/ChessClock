#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "ChessClock/Config.hpp"
#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/Vector2.hpp"

namespace ChessClock
{
    class Transform
    {
        typedef std::vector<TransformPtr> Children;

        Children _children;

    public:
        Vector2 position;
        float rotation;
        float scale;

        Transform(Vector2 const& pos, float rot, float _scale = 1)
            : position(pos), rotation(rot), scale(_scale)
        {
        }

        Vector2 Apply(Vector2 const& point);

        bool Add(TransformPtr ptr)
        {
            if (std::find(_children.begin(), _children.end(), ptr) != _children.end()) 
            {
                return false;
            }

            _children.push_back(ptr);
        }
    };
}


