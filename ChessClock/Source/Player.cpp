#include "ChessClock/Player.hpp"

namespace ChessClock
{
    void PlayerTime::Subtract(float seconds)
    {
        auto millis = seconds / 1000.f;
        auto newMillis = this->millis - millis;
        if (newMillis < 0)
        {
            seconds--;
            if (seconds < 0)
            {
                minutes--;
                if (minutes > 0)
                {
                    seconds += 60;
                }
            }

            newMillis -= 1000;
        }

        millis = newMillis;
    }

    void Player::Pause(bool paused)
    {
    }

    void Player::UpdateTime(float deltaTime)
    {
        RemainingTime.Subtract(deltaTime / 1000.0f);
    }
}
