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
        ENavScreen _current{ ENavScreen::Main };

    public:
        Navigation() = default;

        void Goto(ENavScreen scene);
        void GoBack();
    };
}

