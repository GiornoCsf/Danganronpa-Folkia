#include "KeyHandler.h"
#include "Config.h"
#include "../audio/AudioManager.h"
#include <raylib.h>

void KeyHandler::Update()
{
    confirm = false;

    if (Config::gameMode == Config::GameMode::Title) {
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
            AudioManager::PlaySFX(SFX_CURSOR);
            Config::commandNum--;
            if (Config::commandNum < 0)
                Config::commandNum = 3;
        }
        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
            AudioManager::PlaySFX(SFX_CURSOR);
            Config::commandNum++;
            if (Config::commandNum > 3)
                Config::commandNum = 0;
        }

        confirm = IsKeyPressed(KEY_ENTER);

    // if (IsKeyPressed(KEY_ENTER)) {
    //     AudioManager::PlaySFX(SFX_SELECT);
    //     if (Config::commandNum == 0) {
    //         Config::gameMode = Config::GameMode::Overworld2D;
    //         AudioManager::PlayBGM(BGM_FREE_ROAM);
    //     }
    //     else if (Config::commandNum == 3) {
    //         shouldExit = true;
    //     }
    // }
}
    if (Config::gameMode == Config::GameMode::Overworld2D) {
        up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
        down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
        left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
        right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
        interact = IsKeyDown(KEY_E);
    }

    if (Config::gameMode == Config::GameMode::VisualNovel) {
        confirm = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE);
    }
}