#include "ChessClock/ResourceBase.hpp"
#include "ChessClock/Transform.hpp"

#include "nlohmann/json.hpp"

using nlohmann::json;

namespace ChessClock
{
    void to_json(json& j, Vector2 const& v)
    {
        j = json{ {"x", v.x}, {"y", v.y} };
    }

    void from_json(const json& j, Vector2& v)
    {
        j.at("x").get_to(v.x);
        j.at("y").get_to(v.y);
    }

    void to_json(json& j, Transform const& tr)
    {
        std::vector<int> childIds;
        j = json{ {"position", tr.position}, {"rotation", tr.rotation}, {"scale", tr.scale}, {"children", childIds} };

        for (auto id : childIds)
        {
            // ??
        }
    }

    void from_json(const json& j, Transform& tr)
    {
        j.at("position").get_to(tr.position);
        j.at("rotation").get_to(tr.rotation);
        j.at("scale").get_to(tr.scale);
    }
}


namespace ChessClock
{
    ResourceBase::ResourceBase(int id)
    {
        nlohmann::json js;
    }
}
