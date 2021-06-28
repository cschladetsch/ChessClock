#pragma once

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/PlayerTime.hpp"
#include "ChessClock/EColor.hpp"

namespace ChessClock
{
    class Player
        : Gambit::NonCopyable
    {
        static inline Logger _log{ "Player" };

        String _name;
        bool _paused{ true };
        EColor _color{ EColor::None };
        PlayerTime _remainingTime{ 0,0,0 };
        ObjectPtr _object;

    public:
        String GetName() const { return _name; }
        EColor GetColor() const { return _color; }
        bool IsPaused() const { return _paused; }

        void SetName(const String& name) { _name = name; }

        Gambit::Minutes GetMinutes() const { return _remainingTime.GetMinutes(); }
        Gambit::Seconds GetSeconds() const { return _remainingTime.GetSeconds(); }
        Gambit::Seconds GetIncrement() const { return _remainingTime.GetIncrement(); }
        bool HasTimedOut() const { return !_remainingTime.IsPositive(); }

    protected:
        friend class GamePlaying;

        void SetColor(const EColor color) { _color = color; }
        void Pause(bool paused = true);
        void SetTimeControl(TimeControl timeControl);
        void AddMillis(Gambit::MilliSeconds millis) { _remainingTime.AddMillis(millis); }
        void AddSeconds(Gambit::Seconds seconds) { _remainingTime.AddMillis(seconds*1000); }
    };
}
