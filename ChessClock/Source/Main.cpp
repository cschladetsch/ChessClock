#define SDL_MAIN_HANDLED

#include <iostream>

#include "ChessClock/GameRoot.hpp"

using namespace Gambit;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << rang::fg::red << "Error: " << rang::fg::yellow << " Resources folder and config filename required\n" << rang::fg::reset;
        return 1;
    }

    string resourcesPath = argv[1];
    string configName = resourcesPath + argv[2];
    ChessClock::GameRoot root(configName.c_str());
    typedef ChessClock::GameRoot::Context Context;

    return Context(resourcesPath.c_str(),
        [&root](Context& ctx) { return root.Setup(ctx); },
        [&root](Context& ctx) { return root.ProcessEvents(ctx); })
        .Run();
}

