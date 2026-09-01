#include "CTerrainUberSplats.h"

// Reverse engineered from Warcraft III binary

CTerrainUberSplats::CTerrainUberSplats() : m_splatId(0), m_scale(1.0f), m_active(false), m_terrain(nullptr) {}
CTerrainUberSplats::~CTerrainUberSplats() {}

int32_t CTerrainUberSplats::GetSplatId() const { return m_splatId; }
void CTerrainUberSplats::SetSplatId(int32_t id) { m_splatId = id; }
const char* CTerrainUberSplats::GetSplatName() const { return m_splatName.c_str(); }
void CTerrainUberSplats::SetSplatName(const char* name) { m_splatName = name ? name : ""; }
float CTerrainUberSplats::GetScale() const { return m_scale; }
void CTerrainUberSplats::SetScale(float scale) { m_scale = scale; }
bool CTerrainUberSplats::IsActive() const { return m_active; }
void CTerrainUberSplats::SetActive(bool active) { m_active = active; }
CTerrain* CTerrainUberSplats::GetTerrain() const { return m_terrain; }
void CTerrainUberSplats::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
