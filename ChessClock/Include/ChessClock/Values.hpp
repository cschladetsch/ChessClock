#include "ChessClock/Page.hpp"

namespace ChessClock
{
    class Root;

    class Values
        : Gambit::NonCopyable
    {
    public:
        Values() = default;

        int logVerbosity{ 0 };
        bool trackMouse{ false };
        bool debugTick{ false };

        Gambit::FontPtr font;
        Gambit::FontPtr headerFont;
        Gambit::FontPtr footerFont;
        Gambit::NumberFontPtr numberFont;

        Gambit::TexturePtr backBuffer;

        //CJS TODO: move these out
        Gambit::TexturePtr leftNameText;
        Gambit::TexturePtr rightNameText;
        Gambit::TexturePtr versusText;

        Gambit::AtlasPtr atlas;
        Root *Root;
        EPage pageCurrent;
        std::unordered_map<EPage, SharedPtr<PageBase>> pages;

        PageBasePtr GetPage(EPage page) { return pages[page]; }
        PageBasePtr GetCurrentPage() { return pages[pageCurrent]; }
        Gambit::ScenePtr GetCurrentScene() { return GetCurrentPage()->Scene; }
        GameBasePtr GetCurrentGame() { return GetCurrentPage()->GameBase; }

    };
}

