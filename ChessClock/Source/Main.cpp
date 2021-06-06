#define SDL_MAIN_HANDLED

#include <iostream>
#include "ChessClock/MainScene.hpp"

using namespace Gambit;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Resources folder required\n";
        return 1;
    }

    ChessClock::MainScene scene;
    typedef ChessClock::MainScene::Context Ctx;

    return Ctx(argv[1],
        [&scene](Ctx& ctx) { return scene.Setup(ctx); },
        [&scene](Ctx& ctx) { return scene.ProcessEvents(ctx); })
        .Run();
}

