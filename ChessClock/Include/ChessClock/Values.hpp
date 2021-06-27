#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/GameRoot.hpp"

namespace ChessClock
{
    using namespace Gambit;

    class Values
        : NonCopyable
    {
    public:
        Values() = default;

        FontPtr font;
        FontPtr headerFont;
        FontPtr footerFont;

        TexturePtr backBuffer;
        TexturePtr leftNameText;
        TexturePtr rightNameText;
        TexturePtr versusText;

        Rect textBounds;
        NumberFontPtr numberFont;
        AtlasPtr atlas;

        GameRootPtr gameRoot;
        GameBasePtr game;
        ScenePtr sceneCurrent;

        ScenePtr sceneSplash;
        ScenePtr scenePlaying;
        ScenePtr sceneSettings;
        ScenePtr sceneAbout;

        GameSplashPtr gameSplash;
        GamePlayingPtr gamePlaying;
        GameSettingsPtr gameSettings;
        GameAboutPtr gameAbout;

        bool trackMouse{ false };
        bool debugTick{ false };
    };
}

