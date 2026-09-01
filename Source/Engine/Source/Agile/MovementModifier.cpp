#include "MovementModifier.h"

// Reverse engineered from Warcraft III binary
// Address: 0x78E417

MovementModifier::MovementModifier() : CModifier(), m_speedMultiplier(1.0f), m_acceleration(0.0f) {
    // Virtual table set in constructor
}

MovementModifier::~MovementModifier() {
    // Virtual destructor
}

float MovementModifier::GetSpeedMultiplier() const {
    return m_speedMultiplier;
}

void MovementModifier::SetSpeedMultiplier(float multiplier) {
    m_speedMultiplier = multiplier;
}

float MovementModifier::GetAcceleration() const {
    return m_acceleration;
}

void MovementModifier::SetAcceleration(float acceleration) {
    m_acceleration = acceleration;
}
