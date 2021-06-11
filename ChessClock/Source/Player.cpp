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
        RemainingTime.Reset(timeControl);
    }

    void Player::UpdateTime(MilliSeconds millisConsumed)
    {
        if (_paused)
        {
            return;
        }

        RemainingTime.Subtract(millisConsumed);
        RemainingTime.Add(IncrementSeconds*1000);

        if (!RemainingTime.IsPositive())
        {
            _timedOutTime = SDL_GetTicks();
            _timedOut = true;
            LOG_INFO() << LOG_VALUE(_color) << LOG_VALUE(_timedOutTime) << "\n";
            return;
        }
    }
}
