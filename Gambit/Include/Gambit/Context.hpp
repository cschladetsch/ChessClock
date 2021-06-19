#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/ThirdParty/SDL_ttf.hpp"
#include "Gambit/Renderer.hpp"
#include "Gambit/ResourceManager.hpp"

namespace Gambit
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
            CreateRenderer();
        }

        Context(const char* resourceFolder, ContextFunction setup, ContextFunction processEvents)
            : resources(renderer, resourceFolder)
        {
            CreateRenderer();
            TTF_Init();

            setup(*this);
            eventProcessors.push_back(processEvents);
        }

        ~Context()
        {
            renderer.Destroy();
            TTF_Quit();
            SDL_Quit();
        }

        float GetSecondsSinceStart()
        {
            return SDL_GetTicks() / 1000.0f;
        }

        void CreateRenderer()
        {
            if (!renderer.Construct("Chess Clock"))
            {
                LOG_ERROR() << "Failed to initialise Renderer\n";
                exit(1);
            }
        }

        int Run()
        {
            try
            {
                while (Execute(eventProcessors) && Execute(steps))
                    ;
            }
            catch (std::exception &e)
            {
                LOG_ERROR() << "Exception: " << fg::red << e.what() << std::endl;
                return 1;
            }

            return 0;
        }

        bool Execute(std::vector<ContextFunction> &funcs)
        {
            auto dupes = funcs;
            auto func = dupes.begin();
            while (func != dupes.end())
            {
                try
                {
                    if (!(*func)(*this))
                    {
                        LOG_ERROR() << "Removing failed stage\n";
                        func = dupes.erase(func);
                    }
                    else
                    {
                        ++func;
                    }
                }
                catch (std::exception &e)
                {
                    LOG_ERROR() << "Exception: " << e.what() << ", continuing without\n";
                    func = dupes.erase(func);
                }
            }

            funcs = dupes;

            return true;
        }
    };
}
