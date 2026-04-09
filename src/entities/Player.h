#pragma once
#include "../core/KeyHandler.h"
#include <raylib.h>

class Player
{
public:
    void Load();
    void Update(const KeyHandler& keyH, float dt);
    void Draw();
    void Unload();

private:
    Texture2D spriteSheet{};
    Vector2 position = { 300.0f, 300.0f };

    float speed = 150.0f;

    int currentFrame = 0;
    int currentRow = 0;
    float animationTimer = 0.0f;
    float animationSpeed = 0.15f;
    bool isMoving = false;

    static constexpr int frameWidth = 16;
    static constexpr int frameHeight = 32;
};