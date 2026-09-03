#include "CTerrainHeight.h"
#include "CTerrain.h"

// Reverse engineered from Warcraft III binary

CTerrainHeight::CTerrainHeight() : m_terrain(nullptr) {}
CTerrainHeight::~CTerrainHeight() {}

float CTerrainHeight::GetHeight(int32_t x, int32_t y) const {
    if (m_terrain) return m_terrain->GetHeight(x, y);
    return 0.0f;
}

void CTerrainHeight::SetHeight(int32_t x, int32_t y, float height) {
    if (m_terrain) m_terrain->SetHeight(x, y, height);
}

void CTerrainHeight::SmoothHeight(int32_t x, int32_t y, int32_t radius) {
    if (!m_terrain) return;

    // Smooth height at position (x, y) with given radius
    // This averages the height of surrounding tiles
    float totalHeight = 0.0f;
    int32_t count = 0;

    for (int32_t dy = -radius; dy <= radius; dy++) {
        for (int32_t dx = -radius; dx <= radius; dx++) {
            int32_t tx = x + dx;
            int32_t ty = y + dy;
            if (m_terrain->InBoundsInt(tx, ty)) {
                totalHeight += m_terrain->GetHeight(tx, ty);
                count++;
            }
        }
    }

    if (count > 0) {
        float avgHeight = totalHeight / count;
        m_terrain->SetHeight(x, y, avgHeight);
    }
}

float CTerrainHeight::GetMinHeight() const { return 0.0f; }
float CTerrainHeight::GetMaxHeight() const { return 0.0f; }
float CTerrainHeight::GetAverageHeight() const { return 0.0f; }
CTerrain* CTerrainHeight::GetTerrain() const { return m_terrain; }
void CTerrainHeight::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
