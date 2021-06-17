#include "Gambit/Texture.hpp"
#include "Gambit/TimerFont.hpp"
#include "Gambit/Atlas.hpp"

#include "ChessClock/Game.hpp"
#include "ChessClock/Global.hpp"
#include "ChessClock/MainScene.hpp"
#include "ChessClock/MainScene.Values.hpp"

namespace ChessClock
{
    using namespace Gambit;

    bool MainScene::ParseJson(JsonNext &item)
    {
        auto &key = item.key();

        auto found = _jsonToMember.find(key);
        if (found == _jsonToMember.end())
        {
            LOG_WARN() << "No member named '" << key << "' found in MainScene\n";
            return false;
        }

        (this->*found->second) = item.value();

        return true;
    }

    void MainScene::SetMemberFieldWriters()
    {
        _jsonToMember["font"] = &MainScene::_defaultFont;
        _jsonToMember["atlas"] = &MainScene::_atlasName;
        _jsonToMember["scene"] = &MainScene::_sceneName;
    }

    bool MainScene::Setup(Context& ctx)
    {
        if (!ReadJson(_jsonConfig.c_str()))
            return false;

        ctx.values = std::make_shared<Values>();
        LoadResources(ctx.resources, ctx.renderer, *ctx.values);

        AddStep(ctx, &MainScene::RenderScene);
        AddStep(ctx, &MainScene::StepGame);
        AddStep(ctx, &MainScene::Present);

        Prepare(ctx);

        return true;
    }

    void MainScene::Prepare(Context &ctx)
    {
        Values &values = *ctx.values;
        values.game.SetGameState(EGameState::Playing);
        values.game.SetColor(ESide::Left, EColor::White);
        values.game.SetTimeControl(TimeControl{5, 0, 3});
        values.game.Pause();
    }

    void MainScene::LoadResources(ResourceManager &resources, Renderer &renderer, Values &values)
    {
        values.font = resources.LoadResource<Font>(_defaultFont.c_str(), 125);
        values.headerFont = resources.LoadResource<Font>(_defaultFont.c_str(), 30);
        values.numberFont = resources.CreateResource<TimerFont>("Numbers", values.font);
        values.numberFont->MakeTextures(resources, renderer, Color{ 255,255,255 });
        values.leftNameText = values.headerFont->CreateTexture(resources, renderer, "Spamfilter", { 255,255,255 });
        values.rightNameText = values.headerFont->CreateTexture(resources, renderer, "monoRAIL", { 255,255,255 });
        values.versusText = values.headerFont->CreateTexture(resources, renderer, "vs", { 255,255,255 });
        values.atlas = resources.LoadResource<Atlas>(_atlasName.c_str(), &resources, &renderer);
        values.scene = resources.LoadResource<Scene>(_sceneName.c_str(), &resources, values.atlas);

        auto leftFace = resources.FindObject("left_clock_face");
        auto rightFace = resources.FindObject("right_clock_face");
        values.game.SetFaces(leftFace, rightFace);
    }

    void MainScene::AddStep(Context& ctx, bool(MainScene::* method)(Context&))
    {
        ctx.steps.push_back([this, method](auto& ctx) { return (this->*method)(ctx); });
    }

    bool MainScene::RenderScene(Context& ctx)
    {
        auto& renderer = ctx.renderer;
        auto& values = *ctx.values;

        values.atlas->WriteSprite(renderer, "background", global.ScreenRect);
        values.scene->Render(ctx.renderer);

        int y = 14;
        renderer.WriteTexture(values.leftNameText, Vector2(85, y));
        renderer.WriteTexture(values.versusText, Vector2(400 - 12, y));
        renderer.WriteTexture(values.rightNameText, Vector2(580, y));

        values.debugTick = false;
        return true;
    }

    void DrawTimer(MainScene::Values& values, Renderer &renderer, Vector2 location, Player const& player)
    {
        values.numberFont->DrawTime(renderer, location,
            (uint8_t)player.GetMinutes(), (uint8_t)player.GetSeconds());
    }

    bool MainScene::StepGame(Context &ctx)
    {
        auto &values = *ctx.values;
        auto &renderer = ctx.renderer;
        auto &game = values.game;

        if (!game.IsPaused())
            game.Update();

        Vector2 destPointLeft{ 35, 95 };
        Vector2 destPointRight{ 438, 95 };

        DrawTimer(values, renderer, destPointLeft, game.LeftPlayer());
        DrawTimer(values, renderer, destPointRight, game.RightPlayer());

        return true;
    }

    bool MainScene::Present(Context &ctx)
    {
        return ctx.renderer.Present();
    }
}

