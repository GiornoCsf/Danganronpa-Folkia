#include "Ui.h"
#include "Config.h"

Ui::Ui() = default;

Ui::~Ui()
{
    if (titleFont.texture.id != 0) UnloadFont(titleFont);
    if (textFont.texture.id != 0) UnloadFont(textFont);
}

void Ui::Init()
{
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
    DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);

    //MENU
    text = "CHAPTER SELECT";
    x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    y += Config::tileSize;
    position = {x, y};
    DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);

    //MENU
    text = "EXTRAS";
    x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    y += Config::tileSize;
    position = {x, y};
    DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);

    //MENU
    text = "OPTIONS";
    x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    y += Config::tileSize;
    position = {x, y};
    DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);
}

float Ui::GetCentredTextX(const Font& font, const std::string& text, float fontSize, float spacing)
{
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    return (Config::screenWidth / 2.0f) - (textSize.x / 2.0f);
}