#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/Rect.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    using String = Gambit::string;
    using Gambit::Logger;
    using Gambit::ObjectPtr;
    using Gambit::Vector2;
    using Gambit::Rect;

    template <class Ty>
    using SharedPtr = std::shared_ptr<Ty>;
    
    class GameRoot;
    class GameBase;
    class GameSplash;
    class GamePlaying;
    class GameSettings;
    class GameAbout;
    class Values;
    class PageBase;

    typedef Gambit::Context<Values> Context;

    typedef SharedPtr<PageBase> PageBasePtr;
    typedef SharedPtr<Context> ContextPtr;
    typedef SharedPtr<GameRoot> GameRootPtr;
    typedef SharedPtr<GameBase> GameBasePtr;

    typedef SharedPtr<GameSplash> GameSplashPtr;
    typedef SharedPtr<GamePlaying> GamePlayingPtr;
    typedef SharedPtr<GameSettings> GameSettingsPtr;
    typedef SharedPtr<GameAbout> GameAboutPtr;
}

