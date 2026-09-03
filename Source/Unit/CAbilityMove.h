#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CAbilityMove manages movement abilities

class CAbilityMove {
public:
    CAbilityMove();
    ~CAbilityMove();

    // Move properties
    float GetMoveSpeed() const;
    void SetMoveSpeed(float speed);

    float GetTurnRate() const;
    void SetTurnRate(float rate);

    // Move state
    bool IsMoving() const;
    void SetMoving(bool moving);

    // Move target
    float GetTargetX() const;
    float GetTargetY() const;
    void SetTarget(float x, float y);

protected:
    float m_moveSpeed;
    float m_turnRate;
    bool m_moving;
    float m_targetX;
    float m_targetY;
};
