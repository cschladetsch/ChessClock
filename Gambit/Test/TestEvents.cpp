#include "Gambit/ThirdParty/catch.hpp"
#include "Gambit/ThirdParty/Event.hpp"

using namespace Gambit;
using namespace std;

static int newVal;
static std::string newStr;

void Callback(int val)
{
    newVal = val;
}

struct Class
{
    int newNum;
    string newString;

    void Method1(int n)
    {
        newNum = n;
    }

    void Method2(int n, std::string str)
    {
        newNum = n;
        newString = str;
    }
};

TEST_CASE("Test event system", "[events]")
{
    SECTION("Test function callback")
    {
        Event<int> ev;

        ev.Add(Callback);
        ev(10);
        REQUIRE(newVal == 10);
        ev(20);
        REQUIRE(newVal == 20);
        ev.Remove(Callback);
        ev(30);
        REQUIRE(newVal == 20);
    }

    SECTION("Test class method one value callback")
    {
        Event<int> ev;
        Class klass;
        ev.Add(klass, &Class::Method1);
        ev(10);
        REQUIRE(klass.newNum == 10);
        ev(20);
        REQUIRE(klass.newNum == 20);
        ev.Remove(klass, &Class::Method1);
        REQUIRE(klass.newNum == 20);
    }

    SECTION("Test class method two args callback")
    {
        Event<int, std::string> ev;
        Class klass;
        ev.Add(klass, &Class::Method2);
        ev(10, "foo");
        REQUIRE(klass.newString == "foo");
        REQUIRE(klass.newNum == 10);
    }
}
