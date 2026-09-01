#include "CAngle.h"
#include <cmath>

// Reverse engineered from Warcraft III binary
// Address: 0x82331C

CAngle::CAngle(float angle) : m_angle(0.0f), m_sin(0.0f), m_cos(1.0f), m_flags(0) {
    // Virtual table set in constructor
    Set_(angle);
}

CAngle::~CAngle() {
    // Virtual destructor
}

int CAngle::Calc() {
    // Address: 0x8532596
    // Calculate sin/cos from current angle
    m_sin = std::sin(m_angle);
    m_cos = std::cos(m_angle);
    return 0;
}

int CAngle::Set_(const float& angle) {
    // Address: 0x8532632
    // Normalize angle to [0, 2*PI]
    float normalized = std::fmod(angle, 2.0f * M_PI);
    if (normalized < 0.0f) {
        normalized += 2.0f * M_PI;
    }

    if (normalized != m_angle) {
        m_angle = normalized;
        m_flags |= 0x08;  // Mark as changed
    }

    return Calc();
}

float CAngle::GetRadians() const {
    return m_angle;
}

float CAngle::GetDegrees() const {
    return m_angle * 180.0f / M_PI;
}

float CAngle::GetSin() const {
    return m_sin;
}

float CAngle::GetCos() const {
    return m_cos;
}
