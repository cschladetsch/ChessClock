#include "Gambit/Vector2.hpp"

#include "ChessClock/Root.hpp"
#include "ChessClock/Values.hpp"
#include "ChessClock/GameBase.hpp"

#include "ChessClock/GamePlaying.hpp"

namespace ChessClock
{
    bool Root::ProcessEvents(Context& ctx)
    {
        Values& values = *ctx.Values;
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (values.GetCurrentGame()->ProcessEvents(ctx, event))
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
                            values.GetCurrentGame()->OnPressed(ctx, where);
                            break;
                        }
                    }
                    break;
                }

                case SDL_MOUSEMOTION:
                {
                    if (!ctx.Values->TrackMouse)
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
                            ctx.Values->DebugTick = true;
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
                            values.TrackMouse = !values.TrackMouse;
                            LOG_INFO() << "Tracking mouse: " << values.TrackMouse << "\n";
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

