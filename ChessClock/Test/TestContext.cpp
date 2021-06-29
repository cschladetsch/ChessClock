#if 0
#include "Gambit/ThirdParty/catch.hpp"
#include "ChessClock/Root.hpp"
#include "Gambit/Context.hpp"

using namespace std;
using namespace Gambit;
using namespace ChessClock;

TEST_CASE("Test Chess Clock", "[clock]")
{
    const string resourcesPath = "../ChessClock/Resources/";
    const string configName = resourcesPath + "Test";

    SECTION("Can boot")
    {
        ChessClock::Root(configName.c_str()).Valid;
    }

    SECTION("Can Start")
    {
        ChessClock::Root root(configName.c_str());
        auto context = ChessClock::Context(resourcesPath.c_str(),
            [&root](ChessClock::Context &ctx) { return root.Setup(ctx); },
            [&root](ChessClock::Context &ctx) { return root.ProcessEvents(ctx); });

        REQUIRE(context.Valid);
    }

    SECTION("Can End")
    {
    }

    SECTION("Can use Increment")
    {
    }
}
#endif