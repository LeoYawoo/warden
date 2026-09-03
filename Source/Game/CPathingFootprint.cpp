#include "CPathingFootprint.h"

// Reverse engineered from Warcraft III binary

CPathingFootprint::CPathingFootprint() : m_initialized(false), m_width(0), m_height(0) {}
CPathingFootprint::~CPathingFootprint() { Shutdown(); }

bool CPathingFootprint::Initialize(int32_t width, int32_t height) {
    m_width = width;
    m_height = height;
    m_footprintData.resize(width * height, true);
    m_initialized = true;
    return true;
}

void CPathingFootprint::Shutdown() {
    m_initialized = false;
    m_footprintData.clear();
}

bool CPathingFootprint::IsInitialized() const { return m_initialized; }

void CPathingFootprint::SetFootprint(int32_t x, int32_t y, bool walkable) {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        m_footprintData[y * m_width + x] = walkable;
    }
}

bool CPathingFootprint::IsWalkable(int32_t x, int32_t y) const {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        return m_footprintData[y * m_width + x];
    }
    return false;
}

int32_t CPathingFootprint::GetWidth() const { return m_width; }
int32_t CPathingFootprint::GetHeight() const { return m_height; }
