#pragma once

#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/SplashScene.hpp"
#include "ChessClock/Game.hpp"

namespace ChessClock
{
    using namespace Gambit;

    struct SplashScene::Values
    {
        FontPtr font;
        TexturePtr backGround;
    };
}

