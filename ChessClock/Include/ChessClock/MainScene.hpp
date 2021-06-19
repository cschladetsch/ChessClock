#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Context.hpp"
#include "Gambit/Logger.hpp"
#include "Gambit/JsonReader.hpp"

#include "ChessClock/Config.hpp"

namespace ChessClock
{
    class MainScene
        : JsonReader
    {
        static inline Gambit::Logger _log{ "MainScene" };

        typedef string MainScene:: *Member;
        typedef std::map<string, Member> JsonItemToStringMember;

        JsonItemToStringMember _jsonToMember;
        string _jsonConfig;
        string _defaultFont;
        string _atlasName;
        string _sceneName;
        static int _frameNumber;

    public:
        struct Values;
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        MainScene() = default;
        MainScene(const char *jsonConfig)
            : _jsonConfig(jsonConfig)
        {
            SetMemberFieldWriters();
        }

        bool Setup(Context &);
        bool ProcessEvents(Context &);
        bool Present(Context &);

    protected:
        void SetMemberFieldWriters();
        void Prepare(Context &ctx);
        bool ParseJson(JsonNext &next) override;
        void AddStep(Context&, bool(MainScene::*method)(Context&));

        void LoadResources(ResourceManager &, Renderer &, Values &values);
        void DebugFrameRate();
        bool StepGame(Context& ctx);
        bool RenderScene(Context& ctx);
    };
}

