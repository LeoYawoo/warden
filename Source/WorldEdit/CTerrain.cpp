#include "CTerrain.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CTerrain::CTerrain()
    : m_width(0),
      m_height(0),
      m_tileSize(0) {
}

CTerrain::~CTerrain() {
    Shutdown();
}

int32_t CTerrain::GetWidth() const {
    return m_width;
}

int32_t CTerrain::GetHeight() const {
    return m_height;
}

int32_t CTerrain::GetTileSize() const {
    return m_tileSize;
}

float CTerrain::GetHeight(int32_t x, int32_t y) const {
    if (InBoundsInt(x, y)) {
        return m_heightMap[y * m_width + x];
    }
    return 0.0f;
}

void CTerrain::SetHeight(int32_t x, int32_t y, float height) {
    if (InBoundsInt(x, y)) {
        m_heightMap[y * m_width + x] = height;
    }
}

uint32_t CTerrain::GetFlags(int32_t x, int32_t y) const {
    if (InBoundsInt(x, y)) {
        return m_flagMap[y * m_width + x];
    }
    return 0;
}

void CTerrain::SetFlags(int32_t x, int32_t y, uint32_t flags) {
    if (InBoundsInt(x, y)) {
        m_flagMap[y * m_width + x] = flags;
    }
}

bool CTerrain::IsWater(int32_t x, int32_t y) const {
    if (InBoundsInt(x, y)) {
        return m_waterMap[y * m_width + x];
    }
    return false;
}

void CTerrain::SetWater(int32_t x, int32_t y, bool water) {
    if (InBoundsInt(x, y)) {
        m_waterMap[y * m_width + x] = water;
    }
}

bool CTerrain::InBounds(float x, float y) const {
    return x >= 0.0f && x < static_cast<float>(m_width * m_tileSize) &&
           y >= 0.0f && y < static_cast<float>(m_height * m_tileSize);
}

bool CTerrain::InBoundsInt(int32_t x, int32_t y) const {
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

void CTerrain::AddWeatherArea(CWeatherArea* area) {
    if (area) {
        m_weatherAreas.push_back(area);
    }
}

void CTerrain::RemoveWeatherArea(CWeatherArea* area) {
    auto it = std::find(m_weatherAreas.begin(), m_weatherAreas.end(), area);
    if (it != m_weatherAreas.end()) {
        m_weatherAreas.erase(it);
    }
}

void CTerrain::Initialize(int32_t width, int32_t height, int32_t tileSize) {
    m_width = width;
    m_height = height;
    m_tileSize = tileSize;

    int32_t totalTiles = width * height;
    m_heightMap.resize(totalTiles, 0.0f);
    m_flagMap.resize(totalTiles, 0);
    m_waterMap.resize(totalTiles, false);
}

void CTerrain::Shutdown() {
    m_width = 0;
    m_height = 0;
    m_tileSize = 0;
    m_heightMap.clear();
    m_flagMap.clear();
    m_waterMap.clear();
    m_weatherAreas.clear();
}
