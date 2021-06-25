#include "Gambit/Object.hpp"

#include "ChessClock/UiCallBacks.hpp"

namespace ChessClock
{
    void UiCallBacks::Call(string const& name, ObjectPtr object) const
    {
        auto call = _callbacks.find(object->Callback);
        if (call == _callbacks.end())
        {
            LOG_ERROR() << "No callback for '" << name << "'\n";
            return;
        }
        call->second(object);
    }

    bool UiCallBacks::AddCallback(string const &name, Callback callback)
    {
        if (_callbacks.find(name) != _callbacks.end())
        {
            LOG_ERROR() << "Will not override callback '" << LOG_VALUE(name) << "'\n";
            return false;
        }
        _callbacks[name] = callback;
        return true;
    }

    bool UiCallBacks::RemoveCallback(string const &name)
    {
        return false;
    }

}
