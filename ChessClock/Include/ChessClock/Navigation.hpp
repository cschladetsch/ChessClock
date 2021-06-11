#pragma once

namespace ChessClock
{
    enum class ENavScreen
    {
        Startup,
        None,
        Main,
        Settings,
    };

    class Navigation
    {
    public:
        void Goto(ENavScreen scene);
        void GoBack();
    };
}
