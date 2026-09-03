#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CAbilitySilence manages silence abilities

class CAbilitySilence {
public:
    CAbilitySilence();
    ~CAbilitySilence();

    // Silence properties
    float GetDuration() const;
    void SetDuration(float duration);

    float GetRadius() const;
    void SetRadius(float radius);

    // Silence state
    bool IsActive() const;
    void SetActive(bool active);

protected:
    float m_duration;
    float m_radius;
    bool m_active;
};
