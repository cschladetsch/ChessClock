#include "Gambit/Object.hpp"

#include "ChessClock/UiCallBacks.hpp"

namespace ChessClock
{
    void UiCallBacks::Call(Context &context, ObjectPtr object) const
    {
        const auto call = _callbacks.find(object->Callback);
        if (call == _callbacks.end())
        {
            LOG_ERROR() << "No callback for '" << object->Callback << "'\n";
            return;
        }

        call->second(context, object);
    }

    bool UiCallBacks::AddCallback(String const &name, Callback callback)
    {
        if (_callbacks.find(name) != _callbacks.end())
        {
            LOG_WARN() << "Will not override callback '" << LOG_VALUE(name) << "'\n";
            return false;
        }

        _callbacks[name] = callback;
        return true;
    }

    bool UiCallBacks::RemoveCallback(String const &name)
    {
        const auto call = _callbacks.find(name);
        if (call == _callbacks.end())
        {
            LOG_WARN() << "Attempt to remove unregistered callback '" << name << "'\n";
            return false;
        }

        _callbacks.erase(call);
        return true;
    }
}

