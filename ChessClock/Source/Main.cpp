#define SDL_MAIN_HANDLED

#include <iostream>

#include "ChessClock/GameRoot.hpp"

using namespace Gambit;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << rang::fg::red << "Resources folder and config filename required\n" << rang::fg::reset;
        return 1;
    }

    string resources = argv[1];
    string config = resources + argv[2];
    ChessClock::GameRoot root(config.c_str());
    typedef ChessClock::GameRoot::Context Context;

    return Context(resources.c_str(),
        [&root](Context& ctx) { return root.Setup(ctx); },
        [&root](Context& ctx) { return root.ProcessEvents(ctx); })
        .Run();
}

