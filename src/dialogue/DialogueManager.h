#pragma once

#include <vector>
#include "Dialogue.h"

class DialogueManager
{
public:
    void StartScene(const std::vector<Dialogue>& newLines);
    void Advance();
    bool IsActive() const;
    bool IsFinished() const;

    const Dialogue& GetCurrentLine() const;

private:
    std::vector<Dialogue> lines;
    int currentIndex = 0;
    bool active = false;
    bool finished = false;
};