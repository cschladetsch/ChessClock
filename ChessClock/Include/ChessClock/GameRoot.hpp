#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/JsonReader.hpp"

#include "ChessClock/ForwardReferences.hpp"
#include "ChessClock/Config.hpp"

namespace ChessClock
{
    using namespace Gambit;

    class GameRoot
        : JsonReader<GameRoot>
    {
        static inline Gambit::Logger _log{ "MainScene" };

        typedef string GameRoot:: *Member;
        string _defaultFont;
        string _themeName;
        string _showFps;
        static int _frameNumber;

    public:
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        GameRoot() = default;
        GameRoot(const char *jsonConfig)
            : JsonReader(
                { 
                    {"font", &GameRoot::_defaultFont},
                    {"theme", &GameRoot::_themeName},
                    {"showFps", &GameRoot::_showFps},
                })
        {
            ReadJsonEx(jsonConfig);
        }

        bool Setup(Context &);
        bool ProcessEvents(Context &);
        bool Present(Context &);
        void OnPressed(Context &, Vector2 where);

    protected:
        void DebugFrameRate();

        void Prepare(Context &ctx);
        bool ParseJson(JsonNext &next) override;
        void LoadResources(ResourceManager &, Renderer &, Values &values);
        void SetupGameSprites(ResourceManager &, Renderer &, Values &values);
        void AddStep(Context&, bool(GameRoot::*method)(Context&));

        void SettingsPressed(Context &, ObjectPtr sourceObject);
        void PausePressed(Context &, ObjectPtr sourceObject);
        void VolumePressed(Context &, ObjectPtr sourceObject);

        bool StepGame(Context& ctx);
        bool RenderScene(Context& ctx);
    };
}

