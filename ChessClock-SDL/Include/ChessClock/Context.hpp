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
        Logger _log{ "Context" };

    public:
        Renderer renderer;
        ResourceManager resources;
        shared_ptr<Values> values;

        vector<ContextFunction> steps;
        vector<ContextFunction> eventProcessors;

        Context(const char* resourceFolder)
            : resources(renderer, resourceFolder)
        {
        }

        Context(const char* resourceFolder, ContextFunction setup, ContextFunction step, ContextFunction processEvents)
            : resources(renderer, resourceFolder)
        {
            if (!renderer.Construct("Chess Clock"))
            {
                LOG_ERROR() << "Failed to initialise Renderer\n";
                exit(1);
            }

            TTF_Init();

            setup(*this);
            steps.push_back(step);
            eventProcessors.push_back(processEvents);
        }

        ~Context()
        {
            renderer.Destroy();
            TTF_Quit();
            SDL_Quit();
        }

        bool Run()
        {
            while (Execute(eventProcessors) && Execute(steps))
                ;

            return true;
        }

        bool Execute(std::vector<ContextFunction> &funcs)
        {
            auto dupes = funcs;
            auto func = dupes.begin();
            while (func != dupes.end())
            {
                if (!(*func)(*this))
                {
                    LOG_ERROR() << "Removing failed stage";
                    func = dupes.erase(func);
                }
                else
                {
                    ++func;
                }
            }

            funcs = dupes;

            return true;
        }
    };
}
