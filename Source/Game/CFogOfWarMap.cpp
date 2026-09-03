#include "CFogOfWarMap.h"

// Reverse engineered from Warcraft III binary

CFogOfWarMap::CFogOfWarMap() : m_initialized(false), m_width(0), m_height(0) {}
CFogOfWarMap::~CFogOfWarMap() { Shutdown(); }

bool CFogOfWarMap::Initialize(int32_t width, int32_t height) {
    m_width = width;
    m_height = height;
    m_fogData.resize(width * height, 0);
    m_initialized = true;
    return true;
}

void CFogOfWarMap::Shutdown() {
    m_initialized = false;
    m_fogData.clear();
}

bool CFogOfWarMap::IsInitialized() const { return m_initialized; }

void CFogOfWarMap::SetFogState(int32_t x, int32_t y, int32_t state) {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        m_fogData[y * m_width + x] = static_cast<uint8_t>(state);
    }
}

int32_t CFogOfWarMap::GetFogState(int32_t x, int32_t y) const {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        return m_fogData[y * m_width + x];
    }
    return 0;
}

int32_t CFogOfWarMap::GetWidth() const { return m_width; }
int32_t CFogOfWarMap::GetHeight() const { return m_height; }

void CFogOfWarMap::WorldToCell(float worldX, float worldY, int32_t& cellX, int32_t& cellY) const {
    cellX = static_cast<int32_t>(worldX / 128.0f);
    cellY = static_cast<int32_t>(worldY / 128.0f);
}
