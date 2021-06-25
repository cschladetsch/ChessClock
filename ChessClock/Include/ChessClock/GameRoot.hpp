#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/JsonReader.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    class GameRoot
        : JsonReader<GameRoot>
    {
        static inline Gambit::Logger _log{ "MainScene" };

        typedef string GameRoot:: *Member;
        string _defaultFont;
        string _atlasName;
        string _sceneName;
        string _showFps;
        static int _frameNumber;

    public:
        struct Values;
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        GameRoot() = default;
        GameRoot(const char *jsonConfig)
            : JsonReader(
                { 
                    {"font", &GameRoot::_defaultFont},
                    {"atlas", &GameRoot::_atlasName},
                    {"scene", &GameRoot::_sceneName},
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

        void LeftRockerPressed(Context &, ObjectPtr sourceObject);
        void RightRockerPressed(Context &, ObjectPtr sourceObject);
        void SettingsPressed(Context &, ObjectPtr sourceObject);
        void PausePressed(Context &, ObjectPtr sourceObject);
        void VolumePressed(Context &, ObjectPtr sourceObject);

        void Prepare(Context &ctx);
        bool ParseJson(JsonNext &next) override;
        void AddStep(Context&, bool(GameRoot::*method)(Context&));

        void LoadResources(ResourceManager &, Renderer &, Values &values);
        bool StepGame(Context& ctx);
        bool RenderScene(Context& ctx);
    };
}

