#include "CTerrainWater.h"

// Reverse engineered from Warcraft III binary

CTerrainWater::CTerrainWater() : m_waterLevel(0), m_waterOpacity(1.0f), m_active(false), m_visible(true), m_terrain(nullptr) {}
CTerrainWater::~CTerrainWater() {}

float CTerrainWater::GetWaterLevel() const { return m_waterLevel; }
void CTerrainWater::SetWaterLevel(float level) { m_waterLevel = level; }
float CTerrainWater::GetWaterOpacity() const { return m_waterOpacity; }
void CTerrainWater::SetWaterOpacity(float opacity) { m_waterOpacity = opacity; }
bool CTerrainWater::IsActive() const { return m_active; }
void CTerrainWater::SetActive(bool active) { m_active = active; }
bool CTerrainWater::IsVisible() const { return m_visible; }
void CTerrainWater::SetVisible(bool visible) { m_visible = visible; }
CTerrain* CTerrainWater::GetTerrain() const { return m_terrain; }
void CTerrainWater::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
