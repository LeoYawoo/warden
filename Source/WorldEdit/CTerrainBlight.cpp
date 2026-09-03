#include "CTerrainBlight.h"

// Reverse engineered from Warcraft III binary

CTerrainBlight::CTerrainBlight() : m_enabled(false), m_terrain(nullptr) {}

CTerrainBlight::~CTerrainBlight() {}

void CTerrainBlight::AddBlight(int32_t x, int32_t y, int32_t radius) {
    if (!m_enabled || !m_terrain) return;

    // Add blight at position (x, y) with given radius
    for (int32_t dy = -radius; dy <= radius; dy++) {
        for (int32_t dx = -radius; dx <= radius; dx++) {
            int32_t tx = x + dx;
            int32_t ty = y + dy;
            if (m_terrain->InBoundsInt(tx, ty)) {
                // Set blight flag on terrain
                uint32_t flags = m_terrain->GetFlags(tx, ty);
                flags |= 0x01; // Blight flag
                m_terrain->SetFlags(tx, ty, flags);
            }
        }
    }
}

void CTerrainBlight::RemoveBlight(int32_t x, int32_t y, int32_t radius) {
    if (!m_enabled || !m_terrain) return;

    // Remove blight at position (x, y) with given radius
    for (int32_t dy = -radius; dy <= radius; dy++) {
        for (int32_t dx = -radius; dx <= radius; dx++) {
            int32_t tx = x + dx;
            int32_t ty = y + dy;
            if (m_terrain->InBoundsInt(tx, ty)) {
                // Clear blight flag on terrain
                uint32_t flags = m_terrain->GetFlags(tx, ty);
                flags &= ~0x01; // Clear blight flag
                m_terrain->SetFlags(tx, ty, flags);
            }
        }
    }
}

bool CTerrainBlight::HasBlight(int32_t x, int32_t y) const {
    if (!m_terrain) return false;

    if (m_terrain->InBoundsInt(x, y)) {
        uint32_t flags = m_terrain->GetFlags(x, y);
        return (flags & 0x01) != 0;
    }
    return false;
}

bool CTerrainBlight::IsEnabled() const { return m_enabled; }
void CTerrainBlight::SetEnabled(bool enabled) { m_enabled = enabled; }
CTerrain* CTerrainBlight::GetTerrain() const { return m_terrain; }
void CTerrainBlight::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
