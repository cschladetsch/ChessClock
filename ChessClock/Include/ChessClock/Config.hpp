#pragma once

#include "Gambit/Config.hpp"

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
    
}

