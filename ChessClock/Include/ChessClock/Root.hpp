#pragma once

#include "EPage.hpp"
#include "Gambit/JsonReader.hpp"

#include "ChessClock/ForwardReferences.hpp"
#include "Gambit/Time.hpp"

namespace ChessClock
{
    class Root
        : Gambit::JsonReader<Root>
        , public std::enable_shared_from_this<Root>
    {
        static inline Gambit::Logger _log{ "MainScene" };
        static int _frameNumber;

        typedef String Root:: *Member;

        String _defaultFont;
        String _themeName;
        String _showFps;
        Gambit::TexturePtr _blackTexture;
        int _result{ 0 };
        Gambit::MilliSeconds _transitionTotalTime{ 750 };
        Gambit::MilliSeconds _transitionTime{ 0 };
        Gambit::MilliSeconds _transitionStartTime{ 0 };
        EPage _transitionPage { EPage::None };

    public:
        typedef Gambit::Context<Values> Context;

        static int GetFrameNumber() { return _frameNumber; }

        Root() = default;
        ~Root() = default;

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
        void StartTransitionTo(Context &, EPage next);

    private:
        static void LoadText(Context &context);
        static void CreateObjectTexts(Context &context);
        static void Prepare(Context &);

        bool ParseJson(JsonNext &item) override;
        void MakeScreenOverlay(Context &context);
        void UpdateTransition(Context &context);
        void ShowFrameRate() const;
        void LoadTheme(Context &context);
        void AddStep(Context&, bool(Root::*method)(Context&));
        void LoadPages(Context &context);
        void LoadResources(Context &);
        bool StepGame(Context &);
        bool RenderScene(Context &);
        void UpdateTransitionBlend(Context &) const;
    };
}

