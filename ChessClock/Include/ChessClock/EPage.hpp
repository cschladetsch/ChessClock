#pragma once

#include <ostream>

namespace ChessClock
{
    enum class EPage
    {
        Splash,
        Playing,
        Settings,
        About
    };

    inline std::ostream& operator<<(std::ostream &out, EPage page)
    {
        switch (page)
        {
        case EPage::Splash:
            return out << "Page::Splash";
        case EPage::Playing:
            return out << "Page::Playing";
        case EPage::Settings:
            return out << "Page::Settings";
        case EPage::About:
            return out << "Page::About";
        }

        return out << "Unknown page " << static_cast<int>(page);
    }
}
