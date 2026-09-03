#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CMissile represents a projectile

class CMissile {
public:
    CMissile();
    ~CMissile();

    // Missile properties
    int32_t GetMissileId() const;
    void SetMissileId(int32_t id);

    // Missile position
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    void SetPosition(float x, float y, float z);

    // Missile velocity
    float GetSpeed() const;
    void SetSpeed(float speed);

    // Missile target
    CUnit* GetTarget() const;
    void SetTarget(CUnit* target);

    // Missile state
    bool IsActive() const;
    void SetActive(bool active);

protected:
    int32_t m_missileId;
    float m_x;
    float m_y;
    float m_z;
    float m_speed;
    CUnit* m_target;
    bool m_active;
};
