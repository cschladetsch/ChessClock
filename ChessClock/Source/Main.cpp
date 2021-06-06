#define SDL_MAIN_HANDLED

#include <iostream>
#include "Gambit/Context.hpp"
#include "ChessClock/TestScene.hpp"

using namespace Gambit;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Resources folder required\n";
        return 1;
    }

    ChessClock::MainScene scene;
    typedef ChessClock::MainScene::Ctx Ctx;

    return Ctx(argv[1],
        [&scene](Ctx& ctx) { return scene.Setup(ctx); },
        [&scene](Ctx& ctx) { return scene.Step(ctx); },
        [&scene](Ctx& ctx) { return scene.ProcessEvents(ctx); })
        .Run();
}

