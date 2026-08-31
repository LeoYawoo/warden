#pragma once

#include "C33Matrix.h"

namespace Tempest {
    class C4Quaternion {
    public:
        // Static functions
        static C4Quaternion Nlerp(float ratio, const C4Quaternion &q1, const C4Quaternion &q2);

        static C4Quaternion Slerp(float t, const C4Quaternion &q1, const C4Quaternion &q2);

        C4Quaternion();

        C4Quaternion(float x, float y, float z, float w);

        float Magnitude() const;

        float SquaredMagnitude() const;

        float Dot(const C4Quaternion &q) const;

        C4Quaternion Conjugate() const;

        C4Quaternion Inverse() const;

        C4Quaternion Normalize() const;

        C33Matrix ToMatrix() const;

        C4Quaternion operator*(const C4Quaternion &q) const;

        C4Quaternion operator*(float s) const;

        C4Quaternion operator+(const C4Quaternion &q) const;

        C4Quaternion operator-(const C4Quaternion &q) const;

    public:
        float x;
        float y;
        float z;
        float w;
    };

    C4Quaternion operator*(float s, const C4Quaternion &q);
}


