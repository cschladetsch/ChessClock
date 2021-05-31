#include <vector>

#include "nlohmann/json.hpp"

#include "ChessClock/ResourceBase.hpp"
#include "ChessClock/Transform.hpp"


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
        std::vector<Guid> children;
        for (auto& child : tr.GetChildren())
        {
            children.push_back(child.first.GetGuid());
        }

        j = json{ {"position", tr.position}, {"rotation", tr.rotation}, {"scale", tr.scale}, {"children", children} };
    }

    void from_json(const json& j, Transform& tr)
    {
        j.at("position").get_to(tr.position);
        j.at("rotation").get_to(tr.rotation);
        j.at("scale").get_to(tr.scale);
        auto childIds = j["children"].get<std::vector<std::string>>();
        for (auto& id : childIds)
        {
            tr.AddChild(Guid{ id });
        }
    }
}

namespace ChessClock
{
}
