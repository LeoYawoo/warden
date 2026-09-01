#include "CRegion.h"

// Reverse engineered from Warcraft III binary

CRegion::CRegion()
    : m_regionId(0),
      m_minX(0.0f),
      m_minY(0.0f),
      m_maxX(0.0f),
      m_maxY(0.0f),
      m_enabled(true),
      m_visible(true),
      m_terrain(nullptr) {
}

CRegion::~CRegion() {
}

int32_t CRegion::GetRegionId() const {
    return m_regionId;
}

void CRegion::SetRegionId(int32_t id) {
    m_regionId = id;
}

const char* CRegion::GetRegionName() const {
    return m_regionName.c_str();
}

void CRegion::SetRegionName(const char* name) {
    if (name) {
        m_regionName = name;
    } else {
        m_regionName.clear();
    }
}

float CRegion::GetMinX() const {
    return m_minX;
}

float CRegion::GetMinY() const {
    return m_minY;
}

float CRegion::GetMaxX() const {
    return m_maxX;
}

float CRegion::GetMaxY() const {
    return m_maxY;
}

void CRegion::SetBounds(float minX, float minY, float maxX, float maxY) {
    m_minX = minX;
    m_minY = minY;
    m_maxX = maxX;
    m_maxY = maxY;
}

bool CRegion::IsEnabled() const {
    return m_enabled;
}

void CRegion::SetEnabled(bool enabled) {
    m_enabled = enabled;
}

bool CRegion::IsVisible() const {
    return m_visible;
}

void CRegion::SetVisible(bool visible) {
    m_visible = visible;
}

bool CRegion::ContainsPoint(float x, float y) const {
    return x >= m_minX && x <= m_maxX && y >= m_minY && y <= m_maxY;
}

CTerrain* CRegion::GetTerrain() const {
    return m_terrain;
}

void CRegion::SetTerrain(CTerrain* terrain) {
    m_terrain = terrain;
}
