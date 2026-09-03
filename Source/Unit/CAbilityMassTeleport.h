#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CAbilityMassTeleport manages mass teleport abilities

class CAbilityMassTeleport {
public:
    CAbilityMassTeleport();
    ~CAbilityMassTeleport();

    // Teleport properties
    float GetRadius() const;
    void SetRadius(float radius);

    float GetCastTime() const;
    void SetCastTime(float castTime);

    // Teleport state
    bool IsCasting() const;
    void SetCasting(bool casting);

    // Teleport target
    float GetTargetX() const;
    float GetTargetY() const;
    void SetTarget(float x, float y);

protected:
    float m_radius;
    float m_castTime;
    bool m_casting;
    float m_targetX;
    float m_targetY;
};
