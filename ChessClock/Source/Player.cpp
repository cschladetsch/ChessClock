#include "Gambit/Logger.hpp"

#include "ChessClock/Player.hpp"

namespace ChessClock
{
    void Player::Pause(bool paused)
    {
        _paused = paused;
    }

    void Player::SetTimeControl(TimeControl timeControl)
    {
        _remainingTime.Reset(timeControl);
    }
}

