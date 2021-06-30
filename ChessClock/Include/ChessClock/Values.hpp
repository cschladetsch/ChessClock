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

        ThemeMetaPtr themeMeta;

        Gambit::FontPtr timerFont;
        Gambit::FontPtr smallFont;
        Gambit::FontPtr headerFont;
        Gambit::NumberFontPtr numberFont;

        Gambit::TexturePtr backBuffer;

        //CJS TODO: move these out
        Gambit::TexturePtr leftNameText;
        Gambit::TexturePtr rightNameText;
        Gambit::TexturePtr versusText;

        Gambit::AtlasPtr atlas;
        Root *root;
        EPage pageCurrent;
        std::unordered_map<EPage, SharedPtr<PageBase>> pages;

        PageBasePtr GetPage(EPage page) { return pages[page]; }
        PageBasePtr GetCurrentPage() { return pages[pageCurrent]; }
        Gambit::ScenePtr GetCurrentScene() { return GetCurrentPage()->Scene; }
        GameBasePtr GetCurrentGame() { return GetCurrentPage()->GameBase; }

    };
}

