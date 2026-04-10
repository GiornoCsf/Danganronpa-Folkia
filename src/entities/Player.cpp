#include "Player.h"

void Player::Load()
{
    spriteSheet = LoadTexture("res/sprites/player/player.png");
}

void Player::Update(const KeyHandler& keyH, float dt)
{
    isMoving = false;

    if (keyH.up) {
        position.y -= speed * dt;
        currentRow = 2;
        isMoving = true;
    }
    if (keyH.down) {
        position.y += speed * dt;
        currentRow = 0;
        isMoving = true;
    }
    if (keyH.left) {
        position.x -= speed * dt;
        currentRow = 3;
        isMoving = true;
    }
    if (keyH.right) {
        position.x += speed * dt;
        currentRow = 1;
        isMoving = true;
    }

    if (isMoving) {
        animationTimer += dt;
        if (animationTimer >= animationSpeed)
        {
            animationTimer = 0.0f;
            currentFrame++;
            if (currentFrame >= 4)
                currentFrame = 0;
        }
    }
    else {
        currentFrame = 0;
    }
}

void Player::Draw()
{
    Rectangle source = {
        static_cast<float>(currentFrame * frameWidth),
        static_cast<float>(currentRow * frameHeight),
        static_cast<float>(frameWidth),
        static_cast<float>(frameHeight)
    };

    Rectangle dest = {
        position.x,
        position.y,
        static_cast<float>(frameWidth * 3),
        static_cast<float>(frameHeight * 3)
    };

    DrawTexturePro(
        spriteSheet,
        source,
        dest,
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}

void Player::Unload()
{
    if (spriteSheet.id != 0) {
        UnloadTexture(spriteSheet);
    }
}