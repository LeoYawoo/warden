#include "CAbilityMove.h"

// Reverse engineered from Warcraft III binary

CAbilityMove::CAbilityMove()
    : m_moveSpeed(0.0f), m_turnRate(0.0f), m_moving(false),
      m_targetX(0.0f), m_targetY(0.0f) {
}

CAbilityMove::~CAbilityMove() {}

float CAbilityMove::GetMoveSpeed() const { return m_moveSpeed; }
void CAbilityMove::SetMoveSpeed(float speed) { m_moveSpeed = speed; }

float CAbilityMove::GetTurnRate() const { return m_turnRate; }
void CAbilityMove::SetTurnRate(float rate) { m_turnRate = rate; }

bool CAbilityMove::IsMoving() const { return m_moving; }
void CAbilityMove::SetMoving(bool moving) { m_moving = moving; }

float CAbilityMove::GetTargetX() const { return m_targetX; }
float CAbilityMove::GetTargetY() const { return m_targetY; }

void CAbilityMove::SetTarget(float x, float y) {
    m_targetX = x;
    m_targetY = y;
}
