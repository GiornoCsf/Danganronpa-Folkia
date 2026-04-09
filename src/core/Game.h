#pragma once

#include "KeyHandler.h"
#include "Ui.h"
#include "../entities/Player.h"
#include "../tile/TileManager.h"

class Game
{
public:
    void Run();
    
private:
    void Init();
    void Update(float dt);
    void Draw();
    void Shutdown();

    KeyHandler keyH;
    TileManager tileManager;
    Ui ui;
    Player player;
};