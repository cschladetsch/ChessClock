#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/MainScene.hpp"
#include "ChessClock/Game.hpp"
#include "ChessClock/Global.hpp"

namespace ChessClock
{
    using namespace Gambit;

    struct MainScene::Values
    {
        FontPtr font;
        FontPtr headerFont;
        FontPtr footerFont;
        TexturePtr backBuffer;
        TexturePtr background;
        TexturePtr leftNameText;
        TexturePtr rightNameText;
        TexturePtr versusText;

        Rect textBounds;
        NumberFontPtr numberFont;
        AtlasPtr atlas;
        Navigation navigation;
        Game game{ navigation };
        bool trackMouse;
    };
}
