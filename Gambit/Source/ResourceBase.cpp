#include <vector>

#include "nlohmann/json.hpp"

#include "Gambit/ResourceBase.hpp"
#include "Gambit/Vector2.hpp"

using nlohmann::json;

namespace Gambit
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
}

namespace Gambit
{
}
