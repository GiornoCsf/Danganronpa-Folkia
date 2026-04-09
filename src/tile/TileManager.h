#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include "../core/Config.h"
#include "Tile.h"

class TileManager
{
public:
    void LoadTiles();
    void LoadMap(const std::string& path);
    void Draw();
    void Unload();

private:
    Texture2D tileSheet;

    std::vector<Tile> tiles;

    int map[Config::maxScreenRow][Config::maxScreenCol] = {};
};