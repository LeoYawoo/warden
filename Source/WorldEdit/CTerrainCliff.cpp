#include "CTerrainCliff.h"

// Reverse engineered from Warcraft III binary

CTerrainCliff::CTerrainCliff() : m_cliffId(0), m_cliffLevel(0), m_active(false), m_terrain(nullptr) {}
CTerrainCliff::~CTerrainCliff() {}

int32_t CTerrainCliff::GetCliffId() const { return m_cliffId; }
void CTerrainCliff::SetCliffId(int32_t id) { m_cliffId = id; }
int32_t CTerrainCliff::GetCliffLevel() const { return m_cliffLevel; }
void CTerrainCliff::SetCliffLevel(int32_t level) { m_cliffLevel = level; }
bool CTerrainCliff::IsActive() const { return m_active; }
void CTerrainCliff::SetActive(bool active) { m_active = active; }
CTerrain* CTerrainCliff::GetTerrain() const { return m_terrain; }
void CTerrainCliff::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
