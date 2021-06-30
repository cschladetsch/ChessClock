#pragma once

#include <memory>

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/Rect.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    class Root;
    class GameBase;
    class GameSplash;
    class GamePlaying;
    class GameSettings;
    class GameAbout;
    class Values;
    class PageBase;
    class ThemeMeta;

    typedef SharedPtr<ThemeMeta> ThemeMetaPtr;
    typedef SharedPtr<PageBase> PageBasePtr;
    typedef SharedPtr<Context> ContextPtr;
    typedef SharedPtr<Root> RootPtr;
    typedef SharedPtr<GameBase> GameBasePtr;
    typedef SharedPtr<GameSplash> GameSplashPtr;
    typedef SharedPtr<GamePlaying> GamePlayingPtr;
    typedef SharedPtr<GameSettings> GameSettingsPtr;
    typedef SharedPtr<GameAbout> GameAboutPtr;
}

