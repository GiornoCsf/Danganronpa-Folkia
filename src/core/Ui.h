#pragma once

#include <iostream>
#include <raylib.h>

class DialogueManager;

class Ui
{
public:
    Ui();
    ~Ui();

    void Init(DialogueManager* dialogueManager);
    void Draw();

    int framesCounter = 0;
    int lettersCount = 0;
    const int typeSpeed = 2;
private:
    void DrawTitleScreen();
    void DrawVisualNovel();
    void DrawPlayUI();
    void DrawDialogueBox();
    void DrawSpeakerName(const std::string& speaker);
    void DrawDialogueText(const std::string& text);
    void DrawAdvancePrompt();
    float GetCentredTextX(const Font& font, const std::string& text, float fontSize, float spacing);
    void BlinkingArrow(int x, int y);
    void DrawMenuOption(const std::string& text, int index, float y);

    // ASSETS
    Font titleFont;
    Font textFont;
    Font dialogueFont;
    Texture2D title{};
    Texture2D titleBackground{};
    Texture2D hud{};
    Texture2D spriteTest{};
    Texture2D room{};
    Shader bloom{};
    DialogueManager* dialogueManager = nullptr;
};