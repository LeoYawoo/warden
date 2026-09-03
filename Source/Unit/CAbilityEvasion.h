#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CAbilityEvasion manages evasion abilities

class CAbilityEvasion {
public:
    CAbilityEvasion();
    ~CAbilityEvasion();

    // Evasion properties
    float GetChance() const;
    void SetChance(float chance);

    // Evasion state
    bool IsEvading() const;
    void SetEvading(bool evading);

protected:
    float m_chance;
    bool m_evading;
};
