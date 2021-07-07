#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    class Root;
    class GameBase;
    class PageSplash;
    class GamePlaying;
    class GameSettings;
    class PageAbout;
    class Values;
    class PageBase;
    class ThemeMeta;
    class Player;
    class TimeControl;

    typedef SharedPtr<ThemeMeta> ThemeMetaPtr;
    typedef SharedPtr<PageBase> PageBasePtr;
    typedef SharedPtr<Context> ContextPtr;
    typedef SharedPtr<Root> RootPtr;
    typedef SharedPtr<GameBase> GameBasePtr;
    typedef SharedPtr<PageSplash> GameSplashPtr;
    typedef SharedPtr<GamePlaying> GamePlayingPtr;
    typedef SharedPtr<GameSettings> GameSettingsPtr;
    typedef SharedPtr<PageAbout> GameAboutPtr;

    void DrawTimer(Values const &values, Gambit::Renderer &renderer, const Vector2 &location, TimeControl const &timeControl);
}

