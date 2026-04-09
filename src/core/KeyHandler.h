#pragma once 

class KeyHandler
{
public:
    void Update();
    
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool interact = false;
};