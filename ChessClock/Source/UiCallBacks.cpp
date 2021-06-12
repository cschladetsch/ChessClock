#include "ChessClock/UiCallBacks.hpp"

namespace ChessClock
{
    void UiCallBacks::Call(string const& name) const
    {
        auto call = _callbacks.find(name);
        if (call == _callbacks.end())
        {
            LOG_ERROR() << "No callback for '" << name << "'\n";
            return;
        }
        call->second();
    }
}
