#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/MainScene.hpp"
#include "ChessClock/Game.hpp"

namespace ChessClock
{
    using namespace Gambit;

    struct MainScene::Values
    {
        FontPtr font;
        FontPtr headerFont;
        FontPtr footerFont;

        TexturePtr backBuffer;
        TexturePtr leftNameText;
        TexturePtr rightNameText;
        TexturePtr versusText;

        ScenePtr scene;

        Rect textBounds;
        NumberFontPtr numberFont;
        AtlasPtr atlas;
        Navigation navigation;
        Game game{ navigation };

        bool trackMouse{ false };
        bool debugTick{ false };
    };
}
