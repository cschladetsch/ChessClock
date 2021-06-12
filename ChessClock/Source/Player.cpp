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

    void Player::UpdateTime(MilliSeconds millisConsumed)
    {
        if (_paused)
        {
            return;
        }

        _remainingTime.Subtract(millisConsumed);
        _remainingTime.Add(IncrementSeconds*1000);

        if (!_remainingTime.IsPositive())
        {
            _timedOutTime = TimeNow();
            _timedOut = true;
            LOG_INFO() << LOG_VALUE(_color) << LOG_VALUE(_timedOutTime) << "\n";
            return;
        }
    }
}
