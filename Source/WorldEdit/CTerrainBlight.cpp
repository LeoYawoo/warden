#include "CTerrainBlight.h"

// Reverse engineered from Warcraft III binary

CTerrainBlight::CTerrainBlight() : m_enabled(false), m_terrain(nullptr) {}

CTerrainBlight::~CTerrainBlight() {}

void CTerrainBlight::AddBlight(int32_t x, int32_t y, int32_t radius) {
    (void)x; (void)y; (void)radius;
    // TODO: Implement blight addition
}

void CTerrainBlight::RemoveBlight(int32_t x, int32_t y, int32_t radius) {
    (void)x; (void)y; (void)radius;
    // TODO: Implement blight removal
}

bool CTerrainBlight::HasBlight(int32_t x, int32_t y) const {
    (void)x; (void)y;
    return false;
}

bool CTerrainBlight::IsEnabled() const { return m_enabled; }
void CTerrainBlight::SetEnabled(bool enabled) { m_enabled = enabled; }
CTerrain* CTerrainBlight::GetTerrain() const { return m_terrain; }
void CTerrainBlight::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
