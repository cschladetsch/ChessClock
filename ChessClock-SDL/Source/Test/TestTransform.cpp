#include "Gambit/ThirdParty/catch.hpp"
#include "Gambit/Transform.hpp"

TEST_CASE("Transform cannot add two identical children", "[transform]")
{
	REQUIRE(true);

	SECTION("Cannot add dupe child")
	{
		REQUIRE(false);
	}

}

