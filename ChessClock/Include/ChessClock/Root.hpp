#pragma once

#include "Page.hpp"
#include "Gambit/JsonReader.hpp"

#include "ChessClock/ForwardReferences.hpp"

namespace ChessClock
{
    class Root
        : Gambit::JsonReader<Root>
    {
        static inline Gambit::Logger _log{ "MainScene" };

        typedef String Root:: *Member;
        String _defaultFont;
        String _themeName;
        String _showFps;
        static int _frameNumber;

    public:
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        Root() = default;

        explicit Root(const char *jsonConfig)
            : JsonReader(
                { 
                    {"font", &Root::_defaultFont},
                    {"theme", &Root::_themeName},
                    {"showFps", &Root::_showFps},
                })
        {
            ReadJsonEx(jsonConfig);
        }

        bool Setup(Context &);
        bool ProcessEvents(Context &);
        bool Present(Context &);
        void OnPressed(Context &, const Vector2& where);

        void Transition(Context &, EPage next);

    protected:
        bool ParseJson(JsonNext &item) override;

        void ShowFrameRate() const;

        void Prepare(Context &);
        void LoadResources(Context &);
        void AddStep(Context&, bool(Root::*method)(Context&));

        bool StepGame(Context &);
        bool RenderScene(Context &);
    };
}

