#include "CTerrainBounds.h"
#include "CTerrain.h"

// Reverse engineered from Warcraft III binary

CTerrainBounds::CTerrainBounds() : m_minX(0), m_minY(0), m_maxX(0), m_maxY(0) {}
CTerrainBounds::~CTerrainBounds() {}

void CTerrainBounds::CalculateBounds(const CTerrain* terrain) {
    if (terrain) {
        m_minX = 0.0f;
        m_minY = 0.0f;
        m_maxX = static_cast<float>(terrain->GetWidth() * terrain->GetTileSize());
        m_maxY = static_cast<float>(terrain->GetHeight() * terrain->GetTileSize());
    }
}

bool CTerrainBounds::IsInBounds(float x, float y) const {
    return x >= m_minX && x < m_maxX && y >= m_minY && y < m_maxY;
}

float CTerrainBounds::GetMinX() const { return m_minX; }
float CTerrainBounds::GetMinY() const { return m_minY; }
float CTerrainBounds::GetMaxX() const { return m_maxX; }
float CTerrainBounds::GetMaxY() const { return m_maxY; }
float CTerrainBounds::GetWidth() const { return m_maxX - m_minX; }
float CTerrainBounds::GetHeight() const { return m_maxY - m_minY; }
