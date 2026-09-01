#include "CTerrainClickEvent.h"

// Reverse engineered from Warcraft III binary
// Address: 0x86D7F6

CTerrainClickEvent::CTerrainClickEvent(unsigned int eventType)
    : CEvent(eventType, nullptr),
      m_clickX(0.0f),
      m_clickY(0.0f),
      m_terrain(nullptr),
      m_tileX(0),
      m_tileY(0) {
    // Virtual table set in constructor
}

CTerrainClickEvent::~CTerrainClickEvent() {
    // Virtual destructor
}

float CTerrainClickEvent::GetClickX() const {
    return m_clickX;
}

float CTerrainClickEvent::GetClickY() const {
    return m_clickY;
}

void CTerrainClickEvent::SetClickPosition(float x, float y) {
    m_clickX = x;
    m_clickY = y;
}

CTerrain* CTerrainClickEvent::GetTerrain() const {
    return m_terrain;
}

void CTerrainClickEvent::SetTerrain(CTerrain* terrain) {
    m_terrain = terrain;
}
