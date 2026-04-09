#include "KeyHandler.h"
#include <raylib.h>

void KeyHandler::Update()
{
    up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
    left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    interact = IsKeyDown(KEY_E);
}