#include "ChessClock/Page.hpp"

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

        //CJS TODO: move these out
        TexturePtr leftNameText;
        TexturePtr rightNameText;
        TexturePtr versusText;

        NumberFontPtr numberFont;
        AtlasPtr atlas;

        RootPtr Root;
        //GameBasePtr game;
        //ScenePtr sceneCurrent;

        EPage pageCurrent;
        std::unordered_map<EPage, SharedPtr<PageBase>> pages;

        PageBasePtr GetPage(EPage page) { return pages[page]; }
        PageBasePtr GetCurrentPage() { return pages[pageCurrent]; }
        ScenePtr GetCurrentScene() { return GetCurrentPage()->Scene; }
        GameBasePtr GetCurrentGame() { return GetCurrentPage()->GameBase; }

        //ScenePtr sceneSplash;
        //ScenePtr scenePlaying;
        //ScenePtr sceneSettings;
        //ScenePtr sceneAbout;

        //GameSplashPtr gameSplash;
        //GamePlayingPtr gamePlaying;
        //GameSettingsPtr gameSettings;
        //GameAboutPtr gameAbout;

        int logVerbosity{ 0 };
        bool trackMouse{ false };
        bool debugTick{ false };
    };
}

