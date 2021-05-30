#define SDL_MAIN_HANDLED

#include <iostream>
#include "ChessClock/Context.hpp"
#include "ChessClock/TestScene.hpp"

using namespace ChessClock;
using namespace ChessClock::TestScene;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Resources folder required\n";
        return 1;
    }

    return Context<Values>(argv[1], TestScene::Setup, TestScene::Step, TestScene::ProcessEvents).Run();
}

