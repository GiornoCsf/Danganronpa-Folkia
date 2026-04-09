#pragma once

#include <iostream>
#include <raylib.h>

class Ui
{
public:
    Ui();
    ~Ui();

    void Init();
    void Draw();
private:
    void DrawTitleScreen();
    void DrawPlayUI();
    float GetCentredTextX(const Font& font, const std::string& text, float fontSize, float spacing);
    void BlinkingArrow(int x, int y);
    Font titleFont;
    Font textFont;
    Texture2D titleBackground{};
};