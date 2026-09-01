#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// WEUtilities provides World Editor utility functions

class WEUtilities {
public:
    // Terrain utilities
    static void SetTerrainHeight(CTerrain* terrain, int32_t x, int32_t y, float height);
    static float GetTerrainHeight(CTerrain* terrain, int32_t x, int32_t y);

    // Tile utilities
    static bool IsValidTile(int32_t x, int32_t y, int32_t mapWidth, int32_t mapHeight);
    static int32_t GetTileIndex(int32_t x, int32_t y, int32_t mapWidth);

    // Coordinate utilities
    static void WorldToTile(float worldX, float worldY, int32_t tileSize, int32_t& tileX, int32_t& tileY);
    static void TileToWorld(int32_t tileX, int32_t tileY, int32_t tileSize, float& worldX, float& worldY);

    // Validation utilities
    static bool IsValidFileName(const char* fileName);
    static bool IsValidMapName(const char* mapName);
};
