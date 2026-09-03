#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CAbilityCouple manages couple abilities

class CAbilityCouple {
public:
    CAbilityCouple();
    ~CAbilityCouple();

    // Couple properties
    CUnit* GetPartner() const;
    void SetPartner(CUnit* partner);

    float GetDistance() const;
    void SetDistance(float distance);

    // Couple state
    bool IsCoupled() const;
    void SetCoupled(bool coupled);

protected:
    CUnit* m_partner;
    float m_distance;
    bool m_coupled;
};
