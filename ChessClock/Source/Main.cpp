#define SDL_MAIN_HANDLED

#include <iostream>
#include "ChessClock/MainScene.hpp"

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
    ChessClock::MainScene scene(config.c_str());
    typedef ChessClock::MainScene::Context Ctx;

    return Ctx(resources.c_str(),
        [&scene](Ctx& ctx) { return scene.Setup(ctx); },
        [&scene](Ctx& ctx) { return scene.ProcessEvents(ctx); })
        .Run();
}

