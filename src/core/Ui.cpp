#include "Ui.h"
#include "Config.h"
#include "../dialogue/DialogueManager.h"
#include "../dialogue/Dialogue.h"

bool arrowVisible = true;
int arrowTimer = 0;

Ui::Ui() = default;

Ui::~Ui()
{
    if (titleFont.texture.id != 0) UnloadFont(titleFont);
    if (textFont.texture.id != 0) UnloadFont(textFont);
    UnloadTexture(titleBackground);
}

void Ui::Init(DialogueManager* dm)
{
    dialogueManager = dm;
    title = LoadTexture("res/textures/Danganronpa_folkia_logo.png");
    titleBackground = LoadTexture("res/textures/hopespeak.png");
    spriteTest = LoadTexture("res/sprites/npcs/Makoto.png");
    hud = LoadTexture("res/textures/HUD.png");
    room = LoadTexture("res/textures/room.png");
    titleFont = LoadFontEx("res/fonts/serpentine-sans-icg-bold-oblique.ttf", 64, nullptr, 0); 
    textFont = LoadFontEx("res/fonts/goodbyeDespair.ttf", 32, nullptr, 0);
    dialogueFont = LoadFontEx("res/fonts/NotoSans-Bold.ttf", 32, nullptr, 0);

    bloom = LoadShader(0, "res/shaders/bloom.fs");
    
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
        case Config::GameMode::VisualNovel:
            DrawVisualNovel();
    }
}

void Ui::DrawTitleScreen()
{
    Rectangle source = { 0.0f, 0.0f, (float)titleBackground.width, (float)titleBackground.height};

    Rectangle dest = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    DrawTexturePro(titleBackground, source, dest, { 0, 0 }, 0.0f, WHITE);
    
    // MAIN TITLE
    std::string text = "Danganronpa:Folkia";
    float x = (GetScreenWidth() / 2.0f) - (title.width / 2.0f);
    float y = Config::tileSize * 1.0f;

    float intensity = 2.0f; // High intensity for that neon look
    int intensityLoc = GetShaderLocation(bloom, "intensity");
    SetShaderValue(bloom, intensityLoc, &intensity, SHADER_UNIFORM_FLOAT);

    BeginShaderMode(bloom);
        DrawTexture(title, x, y, WHITE);
    EndShaderMode();
    //DrawTextEx(titleFont, text.c_str(), { x, y }, 64.0f, 2.0f, RAYWHITE);

    float startY = Config::tileSize * 7.5f; 
    float barHeight = Config::tileSize * 0.8f;
    float barWidth = 350.0f;
    float barX = (GetScreenWidth() - barWidth) / 2.0f;

    float highlightY = startY + (Config::commandNum * Config::tileSize * 1.2f) - (barHeight / 4.0f);
    float slant = 20.0f; // How much the bar tilts

    Vector2 topLeft     = { barX - slant, highlightY };
    Vector2 topRight    = { barX + barWidth - slant, highlightY };
    Vector2 bottomRight = { barX + barWidth + slant, highlightY + barHeight };
    Vector2 bottomLeft  = { barX + slant, highlightY + barHeight };


    Vector2 points[4] = { topLeft, bottomLeft, bottomRight, topRight };
    DrawTriangleFan(points, 4, ColorAlpha(BLACK, 0.8f));

   
    DrawLineEx(topLeft, bottomLeft, 4.0f, RAYWHITE);


    DrawLineEx(bottomLeft, bottomRight, 1.0f, ColorAlpha(RAYWHITE, 0.3f));
    DrawLineEx(topRight, topLeft, 1.0f, ColorAlpha(RAYWHITE, 0.3f));

    // NEW GAME
    y = startY;
    //y += Config::tileSize * 6.5f;
    DrawMenuOption("NEW GAME", 0, y);

    // LOAD GAME
    y += Config::tileSize * 1.2f;
    DrawMenuOption("LOAD GAME", 1, y);

    // OPTIONS
    y += Config::tileSize * 1.2f;
    DrawMenuOption("OPTIONS", 2, y);

    // QUIT
    y += Config::tileSize * 1.2f;
    DrawMenuOption("QUIT", 3, y);
}

void Ui::DrawVisualNovel()
{
    ClearBackground(DARKGRAY);
    if (dialogueManager == nullptr || dialogueManager->IsFinished())
        return;

    
    Rectangle source = { 0.0f, 0.0f, (float)room.width, (float)room.height};

    Rectangle dest = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    DrawTexturePro(room, source, dest, { 0, 0 }, 0.0f, WHITE);

    DrawTexture(spriteTest, Config::screenWidth / 2, Config::tileSize * 3, WHITE);
    const Dialogue& line = dialogueManager->GetCurrentLine();
    DrawDialogueBox();
    DrawSpeakerName(line.speaker);
    DrawDialogueText(line.text, line.isThought);
    DrawAdvancePrompt();
}

void Ui::DrawPlayUI()
{
    Rectangle source = { 0.0f, 0.0f, (float)hud.width, (float)hud.height};

    Rectangle dest = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    //DrawTexturePro(hud, source, dest, { 0, 0 }, 0.0f, WHITE);
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

void Ui::DrawDialogueBox()
{
    const int margin = 20;
    const int boxHeight = 160;

    int boxX = margin;
    int boxY = Config::screenHeight - boxHeight - margin;
    int boxWidth = Config::screenWidth - (margin * 2);

    DrawRectangle(boxX, boxY, boxWidth, boxHeight, BLACK);
    DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, RAYWHITE);
}

void Ui::DrawSpeakerName(const std::string& speaker)
{
    if (speaker.empty())
        return;

    Vector2 position = { 40.0f, static_cast<float>(Config::screenHeight - 150) };

    DrawTextEx(dialogueFont, speaker.c_str(), position, 20.0f, 2.0f, RED);
}

void Ui::DrawDialogueText(const std::string& text, bool isThought)
{
    dialogueManager->framesCounter++;
    if (dialogueManager->framesCounter >= dialogueManager->typeSpeed) {
        dialogueManager->framesCounter = 0;
        if (dialogueManager->lettersCount < text.length()) dialogueManager->lettersCount++;
    }
    Vector2 position = { 40.0f, static_cast<float>(Config::screenHeight - 110) };

    std::string visibleText = text.substr(0, dialogueManager->lettersCount);
    Color textColor = isThought ? WHITE : Color{126, 231, 255, 255};
    DrawTextEx(dialogueFont, visibleText.c_str(), position, 32.0f, 2.0f, textColor);
}

void Ui::DrawAdvancePrompt()
{
    const std::string prompt = "Press Enter";
    float x = Config::screenWidth - 210.0f;
    float y = Config::screenHeight - 50.0f;

    DrawTextEx(textFont, prompt.c_str(), { x, y }, 20.0f, 2.0f, GRAY);
}

void Ui::DrawMenuOption(const std::string& text, int index, float y) 
{
    float x = GetCentredTextX(dialogueFont, text, 32.0f, 2.0f);
    Vector2 position = { x, y};

    DrawTextEx(dialogueFont, text.c_str(), position, 32.0f, 2.0f, RAYWHITE);

    if (Config::commandNum == index) {
        BlinkingArrow(x, y);
    }
}