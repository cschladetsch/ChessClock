#include "Gambit/Vector2.hpp"

#include "ChessClock/GameRoot.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/GameBase.hpp"

#include "ChessClock/GamePlaying.hpp"

namespace ChessClock
{
    bool GameRoot::ProcessEvents(Context& ctx)
    {
        Values& values = *ctx.values;
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (values.playing->ProcessEvents(ctx, event))
                continue;

            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                {
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                        {
                            auto where = Vector2{ event.button.x, event.button.y };
                            values.game->OnPressed(ctx, where);
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

                    }
                    break;
                }
            }
        }

        return true;
    }
}

