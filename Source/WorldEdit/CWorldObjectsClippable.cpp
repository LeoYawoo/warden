#include "CWorldObjectsClippable.h"

// Reverse engineered from Warcraft III binary

CWorldObjectsClippable::CWorldObjectsClippable() : m_objectId(0), m_clipped(false), m_visible(true), m_clipRadius(0), m_terrain(nullptr) {}
CWorldObjectsClippable::~CWorldObjectsClippable() {}

int32_t CWorldObjectsClippable::GetObjectId() const { return m_objectId; }
void CWorldObjectsClippable::SetObjectId(int32_t id) { m_objectId = id; }
bool CWorldObjectsClippable::IsClipped() const { return m_clipped; }
void CWorldObjectsClippable::SetClipped(bool clipped) { m_clipped = clipped; }
bool CWorldObjectsClippable::IsVisible() const { return m_visible; }
void CWorldObjectsClippable::SetVisible(bool visible) { m_visible = visible; }
float CWorldObjectsClippable::GetClipRadius() const { return m_clipRadius; }
void CWorldObjectsClippable::SetClipRadius(float radius) { m_clipRadius = radius; }
CTerrain* CWorldObjectsClippable::GetTerrain() const { return m_terrain; }
void CWorldObjectsClippable::SetTerrain(CTerrain* terrain) { m_terrain = terrain; }
