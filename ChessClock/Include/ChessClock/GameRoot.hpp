#pragma once

#include "Gambit/JsonReader.hpp"

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    class GameRoot
        : Gambit::JsonReader<GameRoot>
    {
        static inline Gambit::Logger _log{ "MainScene" };

        typedef String GameRoot:: *Member;
        String _defaultFont;
        String _themeName;
        String _showFps;
        static int _frameNumber;

    public:
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        GameRoot() = default;

        explicit GameRoot(const char *jsonConfig)
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
        void OnPressed(Context&, const Vector2& where);

        void Transition(PageBase next);

    protected:
        bool ParseJson(JsonNext &next) override;

        void ShowFrameRate() const;

        void Prepare(Context &ctx);
        void LoadResources(Gambit::ResourceManager &, Gambit::Renderer &, Values &values);
        void AddStep(Context&, bool(GameRoot::*method)(Context&));

        static void SetupGameSprites(Gambit::ResourceManager &, Gambit::Renderer &, Values &values);

        static void SettingsPressed(Context &, ObjectPtr sourceObject);
        static void PausePressed(Context &, ObjectPtr sourceObject);
        static void VolumePressed(Context &, ObjectPtr sourceObject);

        bool StepGame(Context &context);
        bool RenderScene(Context& ctx);
    };
}

