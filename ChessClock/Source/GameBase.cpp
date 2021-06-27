#include "Gambit/Vector2.hpp"

#include "ChessClock/GameRoot.hpp"
#include "ChessClock/GameBase.hpp"
#include "ChessClock/Values.hpp"

namespace ChessClock
{
    void GameBase::OnPressed(Gambit::Context<Values> & context, Vector2 where) const
    {
        context.values->gameRoot->OnPressed(context, where);
    }
}
