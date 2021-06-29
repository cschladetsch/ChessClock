#pragma once

#include "Page.hpp"
#include "Gambit/JsonReader.hpp"

#include "ChessClock/ForwardReferences.hpp"
#include "Gambit/Time.hpp"

namespace ChessClock
{
    class Root
        : Gambit::JsonReader<Root>
        , public std::enable_shared_from_this<Root>
        //, public Gambit::Testable
    {
        static inline Gambit::Logger _log{ "MainScene" };

        typedef String Root:: *Member;
        String _defaultFont;
        String _themeName;
        String _showFps;
        static int _frameNumber;
        SDL_Texture *_fullscreenBlack;

    public:
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        Root() = default;
        ~Root();

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

    private:
        bool ParseJson(JsonNext &item) override;
        void MakeScreenOverlay(Context &context);

        Gambit::MilliSeconds _transitionTotalTime{ 500 };
        Gambit::MilliSeconds _transitionTime{ 0 };
        Gambit::MilliSeconds _transitionStartTime{ 0 };
        EPage _transitionPage;
        void UpdateTransition(Context &context);

        void ShowFrameRate() const;

        void Prepare(Context &);
        void LoadResources(Context &);
        void AddStep(Context&, bool(Root::*method)(Context&));

        bool StepGame(Context &);
        bool RenderScene(Context &);
    };
}

