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
    hud = LoadTexture("res/textures/HUD.png");
    titleFont = LoadFontEx("res/fonts/serpentine-sans-icg-bold-oblique.ttf", 64, nullptr, 0); 
    textFont = LoadFontEx("res/fonts/goodbyeDespair.ttf", 32, nullptr, 0);
    
    if (titleFont.texture.id != 0) SetTextureFilter(titleFont.texture, TEXTURE_FILTER_BILINEAR);
    if (textFont.texture.id != 0) SetTextureFilter(textFont.texture, TEXTURE_FILTER_BILINEAR);
}

void Ui::Draw() 
{
    switch (Config::gameMode) 
    {
        case Config::GameMode::Title:
            DrawTitleScreen();
            break;
        case Config::GameMode::Overworld2D:
            DrawPlayUI();
            break;
    }
}

void Ui::DrawTitleScreen()
{
    Rectangle source = { 0.0f, 0.0f, (float)titleBackground.width, (float)titleBackground.height};

    Rectangle dest = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    DrawTexturePro(titleBackground, source, dest, { 0, 0 }, 0.0f, WHITE);
    
    // MAIN TITLE
    std::string text = "Danganronpa:Folkia";
    float x = GetCentredTextX(titleFont, text, 64.0f, 2.0f);
    float y = Config::tileSize * 4.0f;

    DrawTextEx(titleFont, text.c_str(), { x, y }, 64.0f, 2.0f, RAYWHITE);

    // NEW GAME
    y += Config::tileSize * 3.5f;
    DrawMenuOption("NEW GAME", 0, y);

    // LOAD GAME
    y += Config::tileSize;
    DrawMenuOption("LOAD GAME", 1, y);

    // OPTIONS
    y += Config::tileSize;
    DrawMenuOption("OPTIONS", 2, y);

    // QUIT
    y += Config::tileSize;
    DrawMenuOption("QUIT", 3, y);

    
}

void Ui::DrawPlayUI()
{
    Rectangle source = { 0.0f, 0.0f, (float)hud.width, (float)hud.height};

    Rectangle dest = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    DrawTexturePro(hud, source, dest, { 0, 0 }, 0.0f, WHITE);
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

void Ui::DrawMenuOption(const std::string& text, int index, float y) 
{
    float x = GetCentredTextX(textFont, text, 32.0f, 2.0f);
    Vector2 position = { x, y};

    DrawTextEx(textFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);

    if (Config::commandNum == index) {
        BlinkingArrow(x, y);
    }
}