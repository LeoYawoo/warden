#pragma once

#include "CModifier.h"

// Reverse engineered from Warcraft III binary
// Address: 0x78E417
// MovementModifier modifies movement properties

class MovementModifier : public CModifier {
public:
    MovementModifier();
    virtual ~MovementModifier();

    // Get movement speed multiplier
    float GetSpeedMultiplier() const;

    // Set movement speed multiplier
    void SetSpeedMultiplier(float multiplier);

    // Get movement acceleration
    float GetAcceleration() const;

    // Set movement acceleration
    void SetAcceleration(float acceleration);

protected:
    float m_speedMultiplier;
    float m_acceleration;
};
