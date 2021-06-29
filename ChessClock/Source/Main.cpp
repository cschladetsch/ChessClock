#define SDL_MAIN_HANDLED

#include "ChessClock/Root.hpp"

using namespace Gambit;
using namespace rang;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << fg::red << "Error: " << fg::yellow << "Resources folder and config filename required.\n" << rang::fg::reset;
        return 1;
    }

    const string resourcesPath = argv[1];
    const string configName = resourcesPath + argv[2];
    ChessClock::Root root(configName.c_str());
    typedef ChessClock::Root::Context Context;

    return Context(resourcesPath.c_str(),
        [&root](Context &ctx) { return root.Setup(ctx); },
        [&root](Context &ctx) { return root.ProcessEvents(ctx); })
        .Run();
}

