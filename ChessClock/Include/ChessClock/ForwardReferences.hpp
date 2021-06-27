#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Vector2.hpp"
#include "Gambit/Rect.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    using string = Gambit::string;
    using Gambit::Logger;
    using Gambit::ObjectPtr;
    using Gambit::Vector2;
    using Gambit::Rect;

    template <class Ty>
    using shared_ptr = std::shared_ptr<Ty>;
    
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

