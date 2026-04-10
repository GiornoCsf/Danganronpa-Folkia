#pragma once

#include "KeyHandler.h"
#include "Ui.h"
#include "../entities/Player.h"
#include "../tile/TileManager.h"
#include "../audio/AudioManager.h"
#include "../dialogue/DialogueManager.h"

class Game
{
public:
    void Run();
    
private:
    void Init();
    void Update(float dt);
    void Draw();
    void Shutdown();

    void StartNewGameScene();

    KeyHandler keyH;
    TileManager tileManager;
    AudioManager aManager;
    DialogueManager dialogueManager;
    Ui ui;
    Player player;
};