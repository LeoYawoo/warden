#include "CTerrainRamp.h"

// Reverse engineered from Warcraft III binary

CTerrainRamp::CTerrainRamp() : m_rampId(0), m_slope(0.0f), m_active(false), m_terrain(nullptr) {}
CTerrainRamp::~CTerrainRamp() {}

int32_t CTerrainRamp::GetRampId() const { return m_rampId; }
void CTerrainRamp::SetRampId(int32_t id) { m_rampId = id; }
float CTerrainRamp::GetSlope() const { return m_slope; }
void CTerrainRamp::SetSlope(float slope) { m_slope = slope; }
bool CTerrainRamp::IsActive() const { return m_active; }
void CTerrainRamp::SetActive(bool active) { m_active = active; }
CTerrain* CTerrainRamp::GetTerrain() const { return m_terrain; }
void CTerrainRamp::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
