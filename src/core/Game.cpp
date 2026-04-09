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

    tileManager.LoadTiles();
    tileManager.LoadMap("res/maps/test.txt");

    player.Load();
}

void Game::Update(float dt)
{
    player.Update(keyH, dt);
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    tileManager.Draw();

    player.Draw();
    EndDrawing();
}

void Game::Shutdown()
{
    tileManager.Unload();
    player.Unload();
    CloseWindow();
}