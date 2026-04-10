#include "Game.h"
#include "Config.h"
#include <raylib.h>

void Game::Run()
{
    Init();

    while (!WindowShouldClose())
    {
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
    ui.Init();

    tileManager.LoadTiles();
    tileManager.LoadMap("res/maps/test.txt");

    player.Load();
}

void Game::Update(float dt)
{
    AudioManager::Update();

    if (Config::gameState == Config::GameState::Play) {
        player.Update(keyH, dt);
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (Config::gameState == Config::GameState::Play) {
        tileManager.Draw();
        player.Draw();
    }
    else if (Config::gameState == Config::GameState::Title)
        ui.Draw();

    EndDrawing();
}

void Game::Shutdown()
{
    tileManager.Unload();
    player.Unload();
    CloseWindow();
}