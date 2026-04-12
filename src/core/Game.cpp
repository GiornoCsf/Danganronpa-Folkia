#include "Game.h"
#include "Config.h"
#include <raylib.h>
#include <vector>
#include "../dialogue/DialogueManager.h"

void Game::Run()
{
    Init();

    while (!keyH.shouldExit && !WindowShouldClose()) {
        float dt = GetFrameTime();
        keyH.Update();
        Update(dt);
        Draw();
    }

    Shutdown();
}

void Game::Init()
{
    InitWindow(Config::screenWidth, Config::screenHeight, Config::name);
    SetTargetFPS(60);

    AudioManager::Init();
    AudioManager::PlayBGM(BGM_TITLE);
    ui.Init(&dialogueManager);

    tileManager.LoadTiles();
    tileManager.LoadMap("res/maps/test.txt");

    player.Load();
}

void Game::Update(float dt)
{
    AudioManager::Update();

    if (Config::gameMode == Config::GameMode::Title)
    {
        if (keyH.confirm)
        {
            AudioManager::PlaySFX(SFX_SELECT);

            if (Config::commandNum == 0) {
                StartNewGameScene();
                AudioManager::PlayBGM(BGM_BEAUTIFUL_DAYS);
            } 
            else if (Config::commandNum == 1) {
                Config::gameMode = Config::GameMode::Overworld2D;
                AudioManager::PlayBGM(BGM_FREE_ROAM);
            }
            else if (Config::commandNum == 3) {
                keyH.shouldExit = true;
            }
        }
    }
    else if (Config::gameMode == Config::GameMode::VisualNovel)
    {
        if (keyH.confirm)
        {
            dialogueManager.Advance();
            AudioManager::PlaySFX(SFX_SELECT);

            if (dialogueManager.IsFinished())
            {
                Config::gameMode = Config::GameMode::Overworld2D;
                AudioManager::PlayBGM(BGM_FREE_ROAM);
            }
        }
    }
    else if (Config::gameMode == Config::GameMode::Overworld2D)
    {
        player.Update(keyH, dt);
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (Config::gameMode == Config::GameMode::Overworld2D) {
        tileManager.Draw();
        player.Draw();
        ui.Draw();
    }
    else if (Config::gameMode == Config::GameMode::Title) {
        ui.Draw();
    }
        
    else if (Config::gameMode == Config::GameMode::VisualNovel) {
        ui.Draw();
    }

    EndDrawing();
}

void Game::StartNewGameScene()
{
    std::vector<Dialogue> introLines =
    {
        { "???", "A quiet hum filled the room.", false },
        { "???", "The screen flickered to life.", false },
        { "You", "What... what?", true },
        { "You", "Where am I?.", true }
    };

    dialogueManager.StartScene(introLines);
    Config::gameMode = Config::GameMode::VisualNovel;
}

void Game::Shutdown()
{
    tileManager.Unload();
    player.Unload();
    CloseWindow();
}