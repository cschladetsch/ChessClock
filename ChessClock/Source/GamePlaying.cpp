#include "Gambit/Object.hpp"
#include "Gambit/TimerFont.hpp"

#include "ChessClock/GamePlaying.hpp"
#include "ChessClock/Root.hpp"
#include "ChessClock/Values.hpp"

namespace ChessClock
{
    void GamePlaying::Prepare(Context &context)
    {
        SetGameState(EGameState::Playing);
        SetColor(ESide::Left, EColor::White);
        SetTimeControl(TimeControl{5, 0, 3});

        AddCallback("SettingsPressed", [this, &context](auto &ctx, auto source) { SettingsPressed(ctx, source); });
        AddCallback("PausePressed", [this, &context](auto &ctx, auto source) { PausePressed(ctx, source); });
        AddCallback("VolumePressed", [this, &context](auto &ctx, auto source) { VolumePressed(ctx, source); });

        SetupGameSprites(context.resources, context.renderer, *context.values);

        Pause();
    }

    void GamePlaying::SettingsPressed(Context &context, ObjectPtr source)
    {
        LOG_INFO() << "Settings pressed from " << LOG_VALUE(source->GetName()) << "\n";
    }

    void GamePlaying::PausePressed(Context &context, ObjectPtr source)
    {
        LOG_INFO() << "Pause pressed from " << LOG_VALUE(source->GetName()) << "\n";
        TogglePause();
    }

    void GamePlaying::VolumePressed(Context &context, ObjectPtr source)
    {
        LOG_INFO () << "Volume pressed from " << LOG_VALUE(source->GetName()) << "\n";
    }

    void GamePlaying::SetupGameSprites(ResourceManager &, Renderer &, Values &values)
    {
        auto &scene = *values.GetPage(EPage::Playing)->Scene;
        const auto leftFace = scene.FindChild("left_clock_face");
        const auto rightFace = scene.FindChild("right_clock_face");
        const auto whitePawn = scene.FindChild("pawn_white");
        const auto blackPawn = scene.FindChild("pawn_black");
        const auto pauseButton = scene.FindChild("icon_pause");
        SetSprites(leftFace, rightFace, whitePawn, blackPawn, pauseButton);
    }

    void DrawTimer(Values& values, Renderer &renderer, const Vector2 &location, Player const& player)
    {
        values.numberFont->DrawTime(renderer, location, static_cast<uint8_t>(player.GetMinutes()), static_cast<uint8_t>(player.GetSeconds()));
    }

    void GamePlaying::Render(Context &ctx) const
    {
        auto& renderer = ctx.renderer;
        auto& values = *ctx.values;

        values.GetCurrentScene()->Render(ctx.renderer);

        int y = 14;
        renderer.WriteTexture(values.leftNameText, Vector2(85, y));
        renderer.WriteTexture(values.versusText, Vector2(400 - 12, y));
        renderer.WriteTexture(values.rightNameText, Vector2(580, y));

        const Vector2 destPointLeft{ 35, 95 };
        const Vector2 destPointRight{ 438, 95 };

        DrawTimer(values, renderer, destPointLeft, LeftPlayer());
        DrawTimer(values, renderer, destPointRight, RightPlayer());
    }

    bool GamePlaying::ProcessEvents(Context &ctx, SDL_Event const &event)
    {
        Values &values = *ctx.values;

        switch (event.type)
        {
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                    {
                        TogglePause();
                        return true;
                    }
                    case SDLK_LEFT:
                    {
                        LOG_VERBOSE(10) << "Pressed left\n";
                        LeftPressed();
                        return true;
                    }
                    case SDLK_RIGHT:
                    {
                        LOG_VERBOSE(10) << "Pressed right\n";
                        RightPressed();
                        return true;
                    }
                }
            }
        }

        return false;
    }

    void GamePlaying::Update(Context &)
    {
        if (_paused)
            return;

        TimeUnit now = TimeNowMillis();
        TimeUnit delta = now - _lastGameTime;
        _gameTime += delta;
        _lastGameTime = now;

        CurrentPlayer().AddMillis(-delta);
    }

    void GamePlaying::ResetGame()
    {
        SetTimeControl(_timeControl);
        SetColor(ESide::Left, EColor::White);
        Pause();
    }

    void GamePlaying::SetGameState(EGameState state)
    {
        LOG_INFO() << "Change state:" << LOG_VALUE(state) << "\n";
    }

    void GamePlaying::SetTimeControl(const TimeControl timeControl)
    {
        if (!_paused)
            Pause();

        _playerLeft.SetTimeControl(timeControl);
        _playerRight.SetTimeControl(timeControl);
    }

    void GamePlaying::SetTimeControl(const ESide side, const TimeControl timeControl)
    {
        GetPlayer(side).SetTimeControl(timeControl);
    }

    EColor GamePlaying::GetPlayerTimedOut() const
    {
        if (_playerLeft.HasTimedOut())
            return _playerLeft.GetColor();

        return _playerRight.HasTimedOut() ? _playerRight.GetColor() : EColor::None;
    }

    void GamePlaying::SetColor(ESide side, EColor color)
    {
        if (side == ESide::Left)
        {
            _playerLeft.SetColor(color);
            _playerRight.SetColor(OtherColor(color));
        }
        else
        {
            _playerRight.SetColor(color);
            _playerLeft.SetColor(OtherColor(color));
        }
    }

    bool GamePlaying::ToggleWhenPaused()
    {
        if (IsPaused() && CurrentPlayer().GetColor() != _currentColor)
        {
            ToggleColor();
            return true;
        }

        return false;
    }

    void GamePlaying::LeftPressed()
    {
        if (ToggleWhenPaused())
            return;

        RockerPressed();
    }

    void GamePlaying::RightPressed()
    {
        if (ToggleWhenPaused())
            return;

        RockerPressed();
    }

    void GamePlaying::RockerPressed()
    {
        if (IsPaused())
        {
            ToggleColor();
            return;
        }

        if (_gameState == EGameState::Ready)
        {
            _gameState = EGameState::Playing;
            _lastGameTime = TimeNowMillis();
            Pause(false);
            return;
        }

        if (_gameState == EGameState::Playing)
            ChangeTurn();
    }

    Player &GamePlaying::GetPlayer(ESide side)
    {
        return side == ESide::Left ? _playerLeft : _playerRight;
    }

    void GamePlaying::SetSprites(const ObjectPtr left, const ObjectPtr right, const ObjectPtr whitePawn, const ObjectPtr blackPawn, ObjectPtr pauseButton)
    {
        _leftFace = left;
        _rightFace = right;
        _whitePawn = whitePawn;
        _blackPawn = blackPawn;
        _pauseButton = pauseButton;
    }

    void GamePlaying::ChangeTurn()
    {
        TimeUnit now = TimeNowMillis();
        TimeUnit delta = now - _lastGameTime;
        _lastGameTime = now;
        Player &currentPlayer = CurrentPlayer();
        currentPlayer.AddMillis(-delta);
        currentPlayer.AddSeconds(currentPlayer.GetIncrement());

        ToggleColor();
    }

    void GamePlaying::ToggleColor()
    {
        _currentColor = OtherColor(_currentColor);

        _leftFace->Tint = _rightFace->Tint = "inactive_player";
        if (LeftPlayer().GetColor() == _currentColor)
            _leftFace->Tint = "active_player";
        else
            _rightFace->Tint = "active_player";
    }

    void GamePlaying::Pause(bool paused)
    {
        _paused = paused;
        if (!paused)
            _lastGameTime = TimeNowMillis();

        CurrentPlayer().Pause(paused);

        _pauseButton->Tint = _paused ? "white" : "active_player";
    }
}

