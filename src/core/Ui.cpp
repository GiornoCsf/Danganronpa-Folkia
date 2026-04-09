#include "Ui.h"
#include "Config.h"

bool arrowVisible = true;
int arrowTimer = 0;

Ui::Ui() = default;

Ui::~Ui()
{
    if (titleFont.texture.id != 0) UnloadFont(titleFont);
    if (textFont.texture.id != 0) UnloadFont(textFont);
    //UnloadTexture(titleBackground);
}

void Ui::Init()
{
    titleBackground = LoadTexture("res/textures/courtroom.png");
    titleFont = LoadFontEx("res/fonts/serpentine-sans-icg-bold-oblique.ttf", 64, nullptr, 0); 
    textFont = LoadFontEx("res/fonts/goodbyeDespair.ttf", 32, nullptr, 0);
    
    if (titleFont.texture.id != 0) SetTextureFilter(titleFont.texture, TEXTURE_FILTER_BILINEAR);
    if (textFont.texture.id != 0) SetTextureFilter(textFont.texture, TEXTURE_FILTER_BILINEAR);
}

void Ui::Draw() 
{
    switch (Config::gameState) 
    {
        case Config::GameState::Title:
            DrawTitleScreen();
            break;
    }
}

void Ui::DrawTitleScreen()
{
    Rectangle source = { 0.0f, 0.0f, (float)titleBackground.width, (float)titleBackground.height};

    Rectangle dest = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    DrawTexturePro(titleBackground, source, dest, { 0, 0 }, 0.0f, WHITE);
    //TITLE NAME
    std::string text = "Danganronpa:Folkia";
    float x = GetCentredTextX(titleFont, text, 64.0f, 2.0f);
    float y = Config::tileSize * 4;
    Vector2 position = { x, y};
    DrawTextEx(titleFont, text.c_str(), position, 64.0f, 2.0f, RAYWHITE);

    //MENU
    text = "NEW GAME";
    x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    y += Config::tileSize * 3.5;
    position = {x, y};

    if (Config::commandNum != 0) {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
    } else {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
         BlinkingArrow(x, y);
    }
   

    //MENU
    text = "CHAPTER SELECT";
    x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    y += Config::tileSize;
    position = {x, y};
    if (Config::commandNum != 1) {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
    } else {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
         BlinkingArrow(x, y);
    }

    //MENU
    text = "EXTRAS";
    x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    y += Config::tileSize;
    position = {x, y};
    if (Config::commandNum != 2) {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
    } else {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
         BlinkingArrow(x, y);
    }

    //MENU
    text = "OPTIONS";
    x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    y += Config::tileSize;
    position = {x, y};
    if (Config::commandNum != 3) {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
    } else {
         DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
         BlinkingArrow(x, y);
    }
}

float Ui::GetCentredTextX(const Font& font, const std::string& text, float fontSize, float spacing)
{
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    return (Config::screenWidth / 2.0f) - (textSize.x / 2.0f);
}

void Ui::BlinkingArrow(int x, int y)
{
    if (arrowVisible)
        DrawText(">", x - Config::tileSize, y, 32.0f, WHITE);

    arrowTimer++;
    if (arrowTimer >= 30) { // toggle every 30 frames (0.5 sec at 60 fps)
        arrowVisible = !arrowVisible;
        arrowTimer = 0;
    }
}