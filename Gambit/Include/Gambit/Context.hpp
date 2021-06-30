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
        Renderer Renderer;
        ResourceManager Resources;
        shared_ptr<Values> Values;
        vector<ContextFunction> Steps;
        vector<ContextFunction> EventProcessors;

        Context(const char* resourceFolder)
            : Resources(Renderer, resourceFolder)
        {
            CreateRenderer();
        }

        Context(const char* resourceFolder, ContextFunction setup, ContextFunction processEvents)
            : Resources(Renderer, resourceFolder)
        {
            CreateRenderer();
            TTF_Init();

            setup(*this);
            EventProcessors.push_back(processEvents);
        }

        ~Context()
        {
            Renderer.Destroy();
            TTF_Quit();
            SDL_Quit();
        }

        static float GetSecondsSinceStart()
        {
            return SDL_GetTicks() / 1000.0f;
        }

        void CreateRenderer()
        {
            if (!Renderer.Construct("Chess Clock"))
            {
                LOG_ERROR() << "Failed to initialise Renderer\n";
                exit(1);
            }
        }

        int Run()
        {
            try
            {
                while (Execute(EventProcessors) && Execute(Steps))
                    ;
            }
            catch (std::exception &e)
            {
                LOG_ERROR() << "Exception: " << fg::red << e.what() << std::endl;
                return 1;
            }

            return 0;
        }

        bool Execute(std::vector<ContextFunction> &functions)
        {
            auto dupes = functions;
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

            functions = dupes;

            return true;
        }
    };
}
