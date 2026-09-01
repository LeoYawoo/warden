#include "CWeatherArea.h"

// Reverse engineered from Warcraft III binary

CWeatherArea::CWeatherArea()
    : m_areaId(0),
      m_minX(0.0f),
      m_minY(0.0f),
      m_maxX(0.0f),
      m_maxY(0.0f),
      m_active(false),
      m_weatherType(0),
      m_terrain(nullptr) {
}

CWeatherArea::~CWeatherArea() {
}

int32_t CWeatherArea::GetAreaId() const {
    return m_areaId;
}

void CWeatherArea::SetAreaId(int32_t id) {
    m_areaId = id;
}

const char* CWeatherArea::GetAreaName() const {
    return m_areaName.c_str();
}

void CWeatherArea::SetAreaName(const char* name) {
    if (name) {
        m_areaName = name;
    } else {
        m_areaName.clear();
    }
}

float CWeatherArea::GetMinX() const {
    return m_minX;
}

float CWeatherArea::GetMinY() const {
    return m_minY;
}

float CWeatherArea::GetMaxX() const {
    return m_maxX;
}

float CWeatherArea::GetMaxY() const {
    return m_maxY;
}

void CWeatherArea::SetBounds(float minX, float minY, float maxX, float maxY) {
    m_minX = minX;
    m_minY = minY;
    m_maxX = maxX;
    m_maxY = maxY;
}

bool CWeatherArea::IsActive() const {
    return m_active;
}

void CWeatherArea::SetActive(bool active) {
    m_active = active;
}

int32_t CWeatherArea::GetWeatherType() const {
    return m_weatherType;
}

void CWeatherArea::SetWeatherType(int32_t type) {
    m_weatherType = type;
}

CTerrain* CWeatherArea::GetTerrain() const {
    return m_terrain;
}

void CWeatherArea::SetTerrain(CTerrain* terrain) {
    m_terrain = terrain;
}
