#pragma once

namespace Config
{
    constexpr char name[12] = "Danganronpa";

    constexpr int originalTileSize = 16;
    constexpr int scale = 3;
    constexpr int tileSize = originalTileSize * scale;

    constexpr int maxScreenCol = 27;
    constexpr int maxScreenRow = 15;

    constexpr int screenWidth = tileSize * maxScreenCol;
    constexpr int screenHeight = tileSize * maxScreenRow;
}