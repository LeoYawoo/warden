#include "WEUtilities.h"
#include "CTerrain.h"
#include <cstring>

// Reverse engineered from Warcraft III binary

void WEUtilities::SetTerrainHeight(CTerrain* terrain, int32_t x, int32_t y, float height) {
    if (terrain) terrain->SetHeight(x, y, height);
}

float WEUtilities::GetTerrainHeight(CTerrain* terrain, int32_t x, int32_t y) {
    if (terrain) return terrain->GetHeight(x, y);
    return 0.0f;
}

bool WEUtilities::IsValidTile(int32_t x, int32_t y, int32_t mapWidth, int32_t mapHeight) {
    return x >= 0 && x < mapWidth && y >= 0 && y < mapHeight;
}

int32_t WEUtilities::GetTileIndex(int32_t x, int32_t y, int32_t mapWidth) {
    return y * mapWidth + x;
}

void WEUtilities::WorldToTile(float worldX, float worldY, int32_t tileSize, int32_t& tileX, int32_t& tileY) {
    tileX = static_cast<int32_t>(worldX / tileSize);
    tileY = static_cast<int32_t>(worldY / tileSize);
}

void WEUtilities::TileToWorld(int32_t tileX, int32_t tileY, int32_t tileSize, float& worldX, float& worldY) {
    worldX = static_cast<float>(tileX * tileSize);
    worldY = static_cast<float>(tileY * tileSize);
}

bool WEUtilities::IsValidFileName(const char* fileName) {
    if (!fileName || strlen(fileName) == 0) return false;
    // Check for invalid characters
    const char* invalid = "<>:\"|?*";
    for (const char* p = invalid; *p; p++) {
        if (strchr(fileName, *p)) return false;
    }
    return true;
}

bool WEUtilities::IsValidMapName(const char* mapName) {
    if (!mapName || strlen(mapName) == 0) return false;
    return strlen(mapName) <= 31;
}
