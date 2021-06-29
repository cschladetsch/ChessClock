#pragma once

#include <utility>

#include "ChessClock/ForwardReferences.hpp"

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

    class PageBase
    {
    public:
        int LogVerbosity{ 0 };
        std::string Name;
        Gambit::AtlasPtr Atlas;
        GameBasePtr GameBase;
        Gambit::ScenePtr Scene;

    protected:
        PageBase(GameBasePtr game, Gambit::ScenePtr scene)
            : GameBase(std::move(game))
            , Scene(std::move(scene))
        { }
    };

    template <class Behaviour>
    class Page
        : public PageBase
    {
    public:
        Page(SharedPtr<Behaviour> const &game, Gambit::ScenePtr const &scene)
            : PageBase(game, scene)
            , Game(game) { }

        SharedPtr<Behaviour> Game;
    };
}

