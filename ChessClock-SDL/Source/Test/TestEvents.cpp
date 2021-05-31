#include "Gambit/ThirdParty/catch.hpp"
#include "Gambit/ThirdParty/Event.hpp"

using namespace Gambit;

static int newVal;

void Callback(int val)
{
    newVal = val;
}

struct Class
{
    int newVal;

    void Method1(int n)
    {
        newVal = n;
    }
};

TEST_CASE("Test event system", "[events]")
{
    SECTION("Test function callback")
    {
        Event<int> num;

        num.Add(Callback);
        num(10);
        REQUIRE(newVal == 10);
        num(20);
        REQUIRE(newVal == 20);
        num.Remove(Callback);
        num(30);
        REQUIRE(newVal == 20);
    }

    SECTION("Test class method callback")
    {
        Event<int> num;

        Class klass;
        num.Add(klass, &Class::Method1);
        num(10);
        REQUIRE(klass.newVal == 10);
        num(20);
        REQUIRE(klass.newVal == 20);
        num.Remove(klass, &Class::Method1);
        REQUIRE(klass.newVal == 20);
    }
}
