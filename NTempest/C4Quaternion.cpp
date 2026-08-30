#include "C4Quaternion.h"
#include <cmath>

using namespace NTempest;

C4Quaternion C4Quaternion::Nlerp(float ratio, const C4Quaternion &q1, const C4Quaternion &q2) {
    float x = (q2.x - q1.x) * ratio + q1.x;
    float y = (q2.y - q1.y) * ratio + q1.y;
    float z = (q2.z - q1.z) * ratio + q1.z;
    float w = (q2.w - q1.w) * ratio + q1.w;

    float m = x * x + y * y + z * z + w * w;
    float v9 = ((m - 0.95906597) * -0.532516) + 1.021435;

    if (m <= 0.91521198) {
        v9 *= (((v9 * v9 * m) - 0.95906597) * -0.532516) + 1.021435;

        if (m <= 0.6521197) {
            v9 *= (((v9 * v9 * m) - 0.95906597) * -0.532516) + 1.021435;
        }
    }

    x *= v9;
    y *= v9;
    z *= v9;
    w *= v9;

    return {x, y, z, w};
}

C4Quaternion C4Quaternion::Slerp(float t, const C4Quaternion &q1, const C4Quaternion &q2) {
    float dot = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

    C4Quaternion q2_adj = q2;

    // If dot is negative, negate one quaternion to take the shorter path
    if (dot < 0.0f) {
        q2_adj.x = -q2_adj.x;
        q2_adj.y = -q2_adj.y;
        q2_adj.z = -q2_adj.z;
        q2_adj.w = -q2_adj.w;
        dot = -dot;
    }

    // If quaternions are very close, use linear interpolation
    if (dot > 0.9995f) {
        return Nlerp(t, q1, q2_adj);
    }

    float theta = acosf(fminf(fmaxf(dot, -1.0f), 1.0f));
    float sinTheta = sinf(theta);
    float w1 = sinf((1.0f - t) * theta) / sinTheta;
    float w2 = sinf(t * theta) / sinTheta;

    return C4Quaternion(
        w1 * q1.x + w2 * q2_adj.x,
        w1 * q1.y + w2 * q2_adj.y,
        w1 * q1.z + w2 * q2_adj.z,
        w1 * q1.w + w2 * q2_adj.w
    );
}

C4Quaternion::C4Quaternion() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

C4Quaternion::C4Quaternion(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {}

float C4Quaternion::SquaredMagnitude() const {
    return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

float C4Quaternion::Magnitude() const {
    return sqrtf(this->SquaredMagnitude());
}

float C4Quaternion::Dot(const C4Quaternion &q) const {
    return this->x * q.x + this->y * q.y + this->z * q.z + this->w * q.w;
}

C4Quaternion C4Quaternion::Conjugate() const {
    return C4Quaternion(-this->x, -this->y, -this->z, this->w);
}

C4Quaternion C4Quaternion::Inverse() const {
    float magSq = this->SquaredMagnitude();
    if (magSq < 1e-10f) {
        return C4Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    }
    C4Quaternion conj = this->Conjugate();
    float invMagSq = 1.0f / magSq;
    return C4Quaternion(
        conj.x * invMagSq,
        conj.y * invMagSq,
        conj.z * invMagSq,
        conj.w * invMagSq
    );
}

C4Quaternion C4Quaternion::Normalize() const {
    float mag = this->Magnitude();
    if (mag < 1e-10f) {
        return C4Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    }
    float invMag = 1.0f / mag;
    return C4Quaternion(
        this->x * invMag,
        this->y * invMag,
        this->z * invMag,
        this->w * invMag
    );
}

C33Matrix C4Quaternion::ToMatrix() const {
    float x2 = this->x * 2.0f;
    float y2 = this->y * 2.0f;
    float z2 = this->z * 2.0f;

    float xx = this->x * x2;
    float yy = this->y * y2;
    float zz = this->z * z2;
    float xy = this->x * y2;
    float xz = this->x * z2;
    float yz = this->y * z2;
    float wx = this->w * x2;
    float wy = this->w * y2;
    float wz = this->w * z2;

    return C33Matrix(
        1.0f - (yy + zz), xy + wz, xz - wy,
        xy - wz, 1.0f - (xx + zz), yz + wx,
        xz + wy, yz - wx, 1.0f - (xx + yy)
    );
}

C4Quaternion C4Quaternion::operator*(const C4Quaternion &q) const {
    return C4Quaternion(
        this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
        this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x,
        this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w,
        this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z
    );
}

C4Quaternion C4Quaternion::operator*(float s) const {
    return C4Quaternion(this->x * s, this->y * s, this->z * s, this->w * s);
}

C4Quaternion C4Quaternion::operator+(const C4Quaternion &q) const {
    return C4Quaternion(this->x + q.x, this->y + q.y, this->z + q.z, this->w + q.w);
}

C4Quaternion C4Quaternion::operator-(const C4Quaternion &q) const {
    return C4Quaternion(this->x - q.x, this->y - q.y, this->z - q.z, this->w - q.w);
}

C4Quaternion NTempest::operator*(float s, const C4Quaternion &q) {
    return q * s;
}
