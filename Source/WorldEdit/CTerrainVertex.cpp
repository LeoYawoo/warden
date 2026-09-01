#include "CTerrainVertex.h"

// Reverse engineered from Warcraft III binary

CTerrainVertex::CTerrainVertex() : m_x(0), m_y(0), m_z(0), m_normalX(0), m_normalY(0), m_normalZ(0), m_active(false), m_terrain(nullptr) {}
CTerrainVertex::~CTerrainVertex() {}

float CTerrainVertex::GetX() const { return m_x; }
float CTerrainVertex::GetY() const { return m_y; }
float CTerrainVertex::GetZ() const { return m_z; }
void CTerrainVertex::SetPosition(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }
float CTerrainVertex::GetNormalX() const { return m_normalX; }
float CTerrainVertex::GetNormalY() const { return m_normalY; }
float CTerrainVertex::GetNormalZ() const { return m_normalZ; }
void CTerrainVertex::SetNormal(float x, float y, float z) { m_normalX = x; m_normalY = y; m_normalZ = z; }
bool CTerrainVertex::IsActive() const { return m_active; }
void CTerrainVertex::SetActive(bool active) { m_active = active; }
CTerrain* CTerrainVertex::GetTerrain() const { return m_terrain; }
void CTerrainVertex::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
