#pragma once

#include "ChessClock/Logger.hpp"
#include "ChessClock/Renderer.hpp"
#include "ChessClock/ResourceManager.hpp"
#include "ChessClock/SDL_ttf.hpp"

namespace ChessClock
{
    template <class Values>
    class Context
    {
    public:
        typedef std::function<bool(Context<Values> &) > ContextFunction;

    private:
        Logger _log{ "MainContext" };

    public:
        Renderer renderer;
        ResourceManager resources;
        ContextFunction step, processEvents;
        Values values;

        Context(const char* resourceFolder, ContextFunction setup, ContextFunction step, ContextFunction processEvents)
            : resources(renderer, resourceFolder)
        {
            if (!renderer.Construct())
            {
                LOG_ERROR() << "Failed to initialise Renderer\n";
                exit(1);
            }

            TTF_Init();

            setup(*this);
            this->step = step;
            this->processEvents = processEvents;
        }

        Context()
        {
            Renderer.Destroy();
            TTF_Quit();
            SDL_Quit();
        }

        bool Run()
        {
            while (Step(*this))
            {
                if (!ProcessEvents(*this))
                {
                    return false;
                }
            }

            return true;
        }
    };
}
