#include "KeyHandler.h"
#include "Config.h"
#include <raylib.h>

void KeyHandler::Update()
{
    if (Config::gameState == Config::GameState::Title)
    {
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
        {
            Config::commandNum--;
            if (Config::commandNum < 0)
                Config::commandNum = 3;
        }
        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
        {
            Config::commandNum++;
            if (Config::commandNum > 3)
                Config::commandNum = 0;
        }

    if (IsKeyPressed(KEY_ENTER)) 
    {
        if (Config::commandNum == 0)
            Config::gameState = Config::GameState::Play;
    }
            
    }
    if (Config::gameState == Config::GameState::Play) 
    {
        up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
        down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
        left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
        right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
        interact = IsKeyDown(KEY_E);
    }
    
}