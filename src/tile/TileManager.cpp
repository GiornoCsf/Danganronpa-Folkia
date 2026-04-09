#include "TileManager.h"
#include <fstream>
#include <iostream>

void TileManager::LoadTiles()
{
    tileSheet = LoadTexture("res/tiles/tiles.png");

    if (tileSheet.id == 0)
    {
        std::cout << "Failed to load tilesheet.\n";
        return;
    }

    Tile blackFloor;
    blackFloor.source = { 0, 0, 16, 16 };
    blackFloor.collision = false;

    Tile whiteFloor;
    whiteFloor.source = { 16, 0, 16, 16 };
    whiteFloor.collision = false;

    Tile carpetLeft;
    carpetLeft.source = { 32, 0, 16, 16};
    carpetLeft.collision = false;

    Tile carpetMiddle;
    carpetMiddle.source = { 48, 0, 16, 16};
    carpetMiddle.collision = false;

    Tile carpetRight;
    carpetRight.source = { 64, 0, 16, 16};

    tiles.push_back(blackFloor); // tile 0
    tiles.push_back(whiteFloor); // tile 1
    tiles.push_back(carpetLeft); // tile 2
    tiles.push_back(carpetMiddle); // tile 3
    tiles.push_back(carpetRight); //tile 4
}

void TileManager::LoadMap(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "Failed to open map file: " << path << "\n";
        return;
    }

    for (int row = 0; row < Config::maxScreenRow; row++)
    {
        for (int col = 0; col < Config::maxScreenCol; col++)
        {
            if (!(file >> map[row][col]))
            {
                std::cout << "Failed reading map data at row " << row
                          << ", col " << col << "\n";
                map[row][col] = 0;
            }
        }
    }

    file.close();
}

void TileManager::Draw()
{
    for (int row = 0; row < Config::maxScreenRow; row++)
    {
        for (int col = 0; col < Config::maxScreenCol; col++)
        {
            int tileNum = map[row][col];

            if (tileNum < 0 || tileNum >= static_cast<int>(tiles.size()))
            {
                std::cout << "Invalid tile index at row " << row
                          << ", col " << col
                          << ": " << tileNum << "\n";
                continue;
            }

            Tile& tile = tiles[tileNum];

            Rectangle dest = {
                static_cast<float>(col * Config::tileSize),
                static_cast<float>(row * Config::tileSize),
                static_cast<float>(Config::tileSize),
                static_cast<float>(Config::tileSize)
            };

            DrawTexturePro(
                tileSheet,
                tile.source,
                dest,
                { 0.0f, 0.0f },
                0.0f,
                WHITE
            );
        }
    }
}

void TileManager::Unload()
{
    if (tileSheet.id != 0)
    {
        UnloadTexture(tileSheet);
    }
}