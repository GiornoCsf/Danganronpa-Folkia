#include "DialogueManager.h"

void DialogueManager::StartScene(const std::vector<Dialogue>& newLines)
{
    lines = newLines;
    currentIndex = 0;
    active = !lines.empty();
    finished = lines.empty();
}

void DialogueManager::Advance()
{
    if (!active || finished)
        return;

    currentIndex++;
    lettersCount = 0;

    if (currentIndex >= static_cast<int>(lines.size())) {
        finished = true;
        active = false;
    }
}

bool DialogueManager::IsActive() const 
{
    return active;
}

bool DialogueManager::IsFinished() const
{
    return finished;
}

const Dialogue& DialogueManager::GetCurrentLine() const
{
    return lines[currentIndex];
}