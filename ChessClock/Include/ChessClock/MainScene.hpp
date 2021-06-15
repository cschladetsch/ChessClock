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
        typedef std::unordered_map<string, Member> JsonItemToMember;

        JsonItemToMember _jsonToMember;
        string _jsonConfig;
        string _defaultFont;
        string _atlasName;
        string _sceneName;

    public:
        struct Values;
        typedef Gambit::Context<Values> Context;

        MainScene() = default;
        MainScene(const char *jsonConfig)
            : _jsonConfig(jsonConfig)
        {
            SetMemberFieldWriters();
        }

        bool Setup(Context &);
        bool StepGame(Context& ctx);
        bool ProcessEvents(Context &);
        bool Present(Context &);
        bool RenderScene(Context& ctx);

    protected:
        void SetMemberFieldWriters();
        void AddStep(Context&, bool(MainScene::*method)(Context&));
        bool ParseJson(JsonNext &next) override;
    };
}

