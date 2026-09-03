#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CAbilityCriticalStrike manages critical strike abilities

class CAbilityCriticalStrike {
public:
    CAbilityCriticalStrike();
    ~CAbilityCriticalStrike();

    // Critical strike properties
    float GetChance() const;
    void SetChance(float chance);

    float GetMultiplier() const;
    void SetMultiplier(float multiplier);

    // Critical strike state
    bool IsCritical() const;
    void SetCritical(bool critical);

protected:
    float m_chance;
    float m_multiplier;
    bool m_critical;
};
