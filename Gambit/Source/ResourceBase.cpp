#include <vector>

#include "Gambit/ThirdParty/Json.hpp"
#include "Gambit/ResourceBase.hpp"
#include "Gambit/Vector2.hpp"

namespace Gambit
{
    void to_json(Json& j, Vector2 const& v)
    {
        j = Json{ {"x", v.x}, {"y", v.y} };
    }

    void from_json(const Json& j, Vector2& v)
    {
        j.at("x").get_to(v.x);
        j.at("y").get_to(v.y);
    }
}

namespace Gambit
{
}
