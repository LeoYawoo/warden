#include "CTerrainTextures.h"

// Reverse engineered from Warcraft III binary

CTerrainTextures::CTerrainTextures() : m_textureId(0), m_active(false), m_terrain(nullptr) {}
CTerrainTextures::~CTerrainTextures() {}

int32_t CTerrainTextures::GetTextureId() const { return m_textureId; }
void CTerrainTextures::SetTextureId(int32_t id) { m_textureId = id; }
const char* CTerrainTextures::GetTextureName() const { return m_textureName.c_str(); }
void CTerrainTextures::SetTextureName(const char* name) { m_textureName = name ? name : ""; }
bool CTerrainTextures::IsActive() const { return m_active; }
void CTerrainTextures::SetActive(bool active) { m_active = active; }
CTerrain* CTerrainTextures::GetTerrain() const { return m_terrain; }
void CTerrainTextures::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
