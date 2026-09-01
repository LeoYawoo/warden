#include "CWorldObjects.h"

// Reverse engineered from Warcraft III binary

CWorldObjects::CWorldObjects()
    : m_objectId(0),
      m_objectType(0),
      m_x(0.0f),
      m_y(0.0f),
      m_z(0.0f),
      m_rotation(0.0f),
      m_scaleX(1.0f),
      m_scaleY(1.0f),
      m_scaleZ(1.0f),
      m_visible(true),
      m_selectable(true),
      m_lifetime(0.0f),
      m_age(0.0f),
      m_terrain(nullptr) {
}

CWorldObjects::~CWorldObjects() {
}

int32_t CWorldObjects::GetObjectId() const {
    return m_objectId;
}

void CWorldObjects::SetObjectId(int32_t id) {
    m_objectId = id;
}

const char* CWorldObjects::GetObjectName() const {
    return m_objectName.c_str();
}

void CWorldObjects::SetObjectName(const char* name) {
    if (name) {
        m_objectName = name;
    } else {
        m_objectName.clear();
    }
}

int32_t CWorldObjects::GetObjectType() const {
    return m_objectType;
}

void CWorldObjects::SetObjectType(int32_t type) {
    m_objectType = type;
}

float CWorldObjects::GetX() const {
    return m_x;
}

float CWorldObjects::GetY() const {
    return m_y;
}

float CWorldObjects::GetZ() const {
    return m_z;
}

void CWorldObjects::SetPosition(float x, float y, float z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

float CWorldObjects::GetRotation() const {
    return m_rotation;
}

void CWorldObjects::SetRotation(float rotation) {
    m_rotation = rotation;
}

float CWorldObjects::GetScaleX() const {
    return m_scaleX;
}

float CWorldObjects::GetScaleY() const {
    return m_scaleY;
}

float CWorldObjects::GetScaleZ() const {
    return m_scaleZ;
}

void CWorldObjects::SetScale(float x, float y, float z) {
    m_scaleX = x;
    m_scaleY = y;
    m_scaleZ = z;
}

bool CWorldObjects::IsVisible() const {
    return m_visible;
}

void CWorldObjects::SetVisible(bool visible) {
    m_visible = visible;
}

bool CWorldObjects::IsSelectable() const {
    return m_selectable;
}

void CWorldObjects::SetSelectable(bool selectable) {
    m_selectable = selectable;
}

float CWorldObjects::GetLifetime() const {
    return m_lifetime;
}

void CWorldObjects::SetLifetime(float lifetime) {
    m_lifetime = lifetime;
}

bool CWorldObjects::HasExpired() const {
    return m_lifetime > 0.0f && m_age >= m_lifetime;
}

CTerrain* CWorldObjects::GetTerrain() const {
    return m_terrain;
}

void CWorldObjects::SetTerrain(CTerrain* terrain) {
    m_terrain = terrain;
}
