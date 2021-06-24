#include "Gambit/Vector2.hpp"

#include "ChessClock/MainScene.hpp"
#include "ChessClock/MainScene.Values.hpp"

namespace Gambit
{
    extern bool logRender;
}

namespace ChessClock
{
    bool MainScene::ProcessEvents(Context& ctx)
    {
        Values& values = *ctx.values;
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                {
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                        {
                            LOG_INFO() << "Pressed " << Vector2{ event.button.x, event.button.y} << "\n";
                            break;
                        }
                    }
                    break;
                }

                case SDL_MOUSEMOTION:
                {
                    if (!ctx.values->trackMouse)
                    {
                        continue;
                    }
                    LOG_INFO() << "x: " << event.motion.x << ", y: " << event.motion.y << "\n";
                    break;
                }

                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_d:
                        {
                            ctx.values->debugTick = true;
                            Gambit::logRender = !Gambit::logRender;
                            continue;
                        }

                        case SDLK_ESCAPE:
                        {
                            LOG_INFO() << "Pressed Escape\n";
                            Logger::CloseFile();
                            exit(0);
                            return true;
                        }

                        case SDLK_m:
                        {
                            values.trackMouse = !values.trackMouse;
                            LOG_INFO() << "Tracking mouse: " << values.trackMouse << "\n";
                            return true;
                        }

                        case SDLK_UP:
                        {
                            LOG_INFO() << "Swap sides\n";
                            values.game.SwapColors();
                            break;
                        }

                        case SDLK_LEFT:
                        {
                            LOG_INFO() << "Pressed left\n";
                            values.game.LeftPressed();
                            break;
                        }

                        case SDLK_RIGHT:
                        {
                            LOG_INFO() << "Pressed right\n";
                            values.game.RightPressed();
                            break;
                        }
                    }
                    break;
                }
            }
        }

        return true;
    }
}
