#pragma once

#include "ChessClock/Logger.hpp"
#include "ChessClock/Renderer.hpp"
#include "ChessClock/ResourceManager.hpp"

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
        Renderer Renderer;
        ResourceManager Resources;
        ContextFunction Step, ProcessEvents;
        Values Values;

        Context(const char* resourceFolder, ContextFunction setup, ContextFunction step, ContextFunction processEvents)
            : Resources(Renderer, resourceFolder)
        {
            if (!Renderer.Construct())
            {
                LOG_ERROR() << "Failed to initialise Renderer\n";
                exit(1);
            }

            TTF_Init();

            setup(*this);
            Step = step;
            ProcessEvents = processEvents;
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
