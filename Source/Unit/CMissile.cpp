#include "CMissile.h"

// Reverse engineered from Warcraft III binary

CMissile::CMissile()
    : m_missileId(0), m_x(0.0f), m_y(0.0f), m_z(0.0f),
      m_speed(0.0f), m_target(nullptr), m_active(false) {
}

CMissile::~CMissile() {}

int32_t CMissile::GetMissileId() const { return m_missileId; }
void CMissile::SetMissileId(int32_t id) { m_missileId = id; }

float CMissile::GetX() const { return m_x; }
float CMissile::GetY() const { return m_y; }
float CMissile::GetZ() const { return m_z; }

void CMissile::SetPosition(float x, float y, float z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

float CMissile::GetSpeed() const { return m_speed; }
void CMissile::SetSpeed(float speed) { m_speed = speed; }

CUnit* CMissile::GetTarget() const { return m_target; }
void CMissile::SetTarget(CUnit* target) { m_target = target; }

bool CMissile::IsActive() const { return m_active; }
void CMissile::SetActive(bool active) { m_active = active; }
