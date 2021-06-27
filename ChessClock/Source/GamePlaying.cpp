#include "Gambit/Object.hpp"

#include "ChessClock/GamePlaying.hpp"
#include "ChessClock/GameRoot.hpp"

#include "ChessClock/Values.hpp"
#include "ChessClock/Global.hpp"

namespace ChessClock
{
    void DrawTimer(Values& values, Renderer &renderer, Vector2 location, Player const& player)
    {
        values.numberFont->DrawTime(renderer, location, (uint8_t)player.GetMinutes(), (uint8_t)player.GetSeconds());
    }

    void GamePlaying::Render(Context &ctx) const
    {
        auto& renderer = ctx.renderer;
        auto& values = *ctx.values;

        //values.atlas->WriteSprite(renderer, "background", global.ScreenRect);

        values.sceneCurrent->Render(ctx.renderer);

        int y = 14;
        renderer.WriteTexture(values.leftNameText, Vector2(85, y));
        renderer.WriteTexture(values.versusText, Vector2(400 - 12, y));
        renderer.WriteTexture(values.rightNameText, Vector2(580, y));

        Vector2 destPointLeft{ 35, 95 };
        Vector2 destPointRight{ 438, 95 };

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

                    case SDLK_UP:
                    {
                        LOG_INFO() << "Swap sides\n";
                        SwapColors();
                        return true;
                    }

                    case SDLK_LEFT:
                    {
                        LOG_INFO() << "Pressed left\n";
                        LeftPressed();
                        return true;
                    }

                    case SDLK_RIGHT:
                    {
                        LOG_INFO() << "Pressed right\n";
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

    void GamePlaying::SwapColors()
    {
        std::swap(_playerLeft, _playerRight);
    }

    void GamePlaying::SetTimeControl(TimeControl timeControl)
    {
        if (!_paused)
            Pause();

        _playerLeft.SetTimeControl(timeControl);
        _playerRight.SetTimeControl(timeControl);
    }

    void GamePlaying::SetTimeControl(ESide side, TimeControl timeControl)
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
        else
        {
            if (_gameState == EGameState::Playing)
                ChangeTurn();
        }
    }

    Player &GamePlaying::GetPlayer(ESide side)
    {
        return side == ESide::Left ? _playerLeft : _playerRight;
    }

    void GamePlaying::SetSprites(ObjectPtr left, ObjectPtr right, ObjectPtr whitePawn, ObjectPtr blackPawn, ObjectPtr pauseButton)
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
        LOG_INFO() << LOG_VALUE(paused) << LOG_VALUE(_gameTime/1000.f) << LOG_VALUE(_pauseButton->Tint) << "\n";
    }
}

