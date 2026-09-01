#pragma once

#include "Common/TRefCnt.h"

// Forward declarations
namespace Tempest {
    class CMath;
}

// Reverse engineered from Warcraft III binary
// Address: 0x82331C
// CAngle represents an angle with sin/cos cache

class CAngle {
public:
    CAngle(float angle = 0.0f);
    virtual ~CAngle();

    // Calculate sin/cos from current angle
    int Calc();

    // Set angle value
    int Set_(const float& angle);

    // Get angle in radians
    float GetRadians() const;

    // Get angle in degrees
    float GetDegrees() const;

    // Get sin value
    float GetSin() const;

    // Get cos value
    float GetCos() const;

protected:
    // Virtual table pointer
    float m_angle;  // offset +28 (7 * 4)
    float m_sin;    // offset +32 (8 * 4)
    float m_cos;    // offset +36 (9 * 4)
    unsigned char m_flags;  // offset +13
};
