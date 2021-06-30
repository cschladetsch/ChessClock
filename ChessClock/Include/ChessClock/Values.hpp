#include "EPage.hpp"
#include "ChessClock/Page.hpp"

namespace ChessClock
{
    class Root;

    class Values
        : Gambit::NonCopyable
    {
    public:
        Values() = default;

        int LogVerbosity{ 0 };
        bool TrackMouse{ false };
        bool DebugTick{ false };

        ThemeMetaPtr Theme;

        Gambit::FontPtr TimerFont;
        Gambit::FontPtr SmallFont;
        Gambit::FontPtr HeaderFont;
        Gambit::NumberFontPtr NumberFont;

        Gambit::TexturePtr BackBuffer;

        //CJS TODO: move these out
        Gambit::TexturePtr LeftNameText;
        Gambit::TexturePtr RightNameText;
        Gambit::TexturePtr VersusText;

        Gambit::AtlasPtr Atlas;
        Root *Root;
        EPage PageCurrent;
        std::unordered_map<EPage, SharedPtr<PageBase>> Pages;

        PageBasePtr GetPage(EPage page) { return Pages[page]; }
        PageBasePtr GetCurrentPage() { return Pages[PageCurrent]; }
        Gambit::ScenePtr GetCurrentScene() { return GetCurrentPage()->Scene; }
        GameBasePtr GetCurrentGame() { return GetCurrentPage()->GameBase; }
    };
}

