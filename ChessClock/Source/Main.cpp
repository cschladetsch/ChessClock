#define SDL_MAIN_HANDLED

#include <iostream>
#include "ChessClock/GameRoot.hpp"

using namespace Gambit;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Resources folder and config file required\n";
        return 1;
    }

    string resources = argv[1];
    string config = resources + argv[2];
    ChessClock::GameRoot root(config.c_str());
    typedef ChessClock::GameRoot::Context Ctx;

    auto result = Ctx(resources.c_str(),
        [&root](Ctx& ctx) { return root.Setup(ctx); },
        [&root](Ctx& ctx) { return root.ProcessEvents(ctx); })
        .Run();

    return result;
}

