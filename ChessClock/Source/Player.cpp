#include "Gambit/Logger.hpp"

#include "ChessClock/Player.hpp"

namespace ChessClock
{
    void Player::Pause(bool paused)
    {
        _paused = paused;
        LOG_INFO() << LOG_VALUE(_color) << LOG_VALUE(paused) << "\n";
    }

    void Player::SetTimeControl(TimeControl timeControl)
    {
        _remainingTime.Reset(timeControl);
    }
}

