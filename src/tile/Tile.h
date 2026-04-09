#pragma once
#include <raylib.h>

class Tile
{
public:
    Rectangle source = { 0, 0, 16, 16};
    bool collision = false;
};