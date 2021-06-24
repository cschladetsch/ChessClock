#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/JsonReader.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    class MainScene
        : JsonReader<MainScene>
    {
        static inline Gambit::Logger _log{ "MainScene" };

        typedef string MainScene:: *Member;
        string _defaultFont;
        string _atlasName;
        string _sceneName;
        string _showFps;
        static int _frameNumber;

    public:
        struct Values;
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        MainScene() = default;
        MainScene(const char *jsonConfig)
            : JsonReader(
                { 
                    {"font", &MainScene::_defaultFont},
                    {"atlas", &MainScene::_atlasName},
                    {"scene", &MainScene::_sceneName},
                    {"showFps", &MainScene::_showFps},
                })
        {
            ReadJsonEx(jsonConfig);
        }

        bool Setup(Context &);
        bool ProcessEvents(Context &);
        bool Present(Context &);

    protected:
        void DebugFrameRate();

        void Prepare(Context &ctx);
        bool ParseJson(JsonNext &next) override;
        void AddStep(Context&, bool(MainScene::*method)(Context&));

        void LoadResources(ResourceManager &, Renderer &, Values &values);
        bool StepGame(Context& ctx);
        bool RenderScene(Context& ctx);
    };
}

