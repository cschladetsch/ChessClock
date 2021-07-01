#include "Gambit/Vector2.hpp"

#include "ChessClock/Root.hpp"
#include "ChessClock/GameBase.hpp"
#include "ChessClock/Values.hpp"

namespace ChessClock
{
    void GameBase::OnPressed(Gambit::Context<Values> & context, Vector2 where) const
    {
        context.MyValues->MyRoot->OnPressed(context, where);
    }
}

