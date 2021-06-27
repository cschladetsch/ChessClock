#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/Context.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    using string = std::string;
    
    class GameRoot;
    class GameBase;
    class GamePlaying;
    class Values;

    typedef Gambit::Context<Values> Context;

    typedef shared_ptr<Context> ContextPtr;
    typedef shared_ptr<GameRoot> GameRootPtr;
    typedef shared_ptr<GameBase> GameBasePtr;
    typedef shared_ptr<GamePlaying> GamePlayingPtr;
}

