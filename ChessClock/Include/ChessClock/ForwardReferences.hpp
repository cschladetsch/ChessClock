#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    using String = Gambit::string;
    using Gambit::Logger;
    using Gambit::ObjectPtr;
    using Gambit::Vector2;
    using Gambit::Rect;

    class Values;
    typedef Gambit::Context<Values> Context;

    template <class Ty>
    using SharedPtr = std::shared_ptr<Ty>;
    class Root;
    class GameBase;
    class PageSplash;
    class GamePlaying;
    class PageSettings;
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
    typedef SharedPtr<PageSettings> GameSettingsPtr;
    typedef SharedPtr<PageAbout> GameAboutPtr;

    void DrawTimer(Values const &values, Gambit::Renderer &renderer, const Vector2 &location, TimeControl const &timeControl);
}

