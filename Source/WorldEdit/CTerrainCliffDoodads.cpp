#include "CTerrainCliffDoodads.h"

// Reverse engineered from Warcraft III binary

CTerrainCliffDoodads::CTerrainCliffDoodads() : m_doodadId(0), m_doodadType(0), m_active(false), m_terrain(nullptr) {}
CTerrainCliffDoodads::~CTerrainCliffDoodads() {}

int32_t CTerrainCliffDoodads::GetDoodadId() const { return m_doodadId; }
void CTerrainCliffDoodads::SetDoodadId(int32_t id) { m_doodadId = id; }
int32_t CTerrainCliffDoodads::GetDoodadType() const { return m_doodadType; }
void CTerrainCliffDoodads::SetDoodadType(int32_t type) { m_doodadType = type; }
bool CTerrainCliffDoodads::IsActive() const { return m_active; }
void CTerrainCliffDoodads::SetActive(bool active) { m_active = active; }
CTerrain* CTerrainCliffDoodads::GetTerrain() const { return m_terrain; }
void CTerrainCliffDoodads::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
