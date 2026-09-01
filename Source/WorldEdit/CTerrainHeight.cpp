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
    (void)x; (void)y; (void)radius;
    // TODO: Implement height smoothing
}

float CTerrainHeight::GetMinHeight() const { return 0.0f; }
float CTerrainHeight::GetMaxHeight() const { return 0.0f; }
float CTerrainHeight::GetAverageHeight() const { return 0.0f; }
CTerrain* CTerrainHeight::GetTerrain() const { return m_terrain; }
void CTerrainHeight::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
