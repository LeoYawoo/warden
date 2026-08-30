#include "C4Plane.h"
#include "C3Vector.h"
#include <cmath>

using namespace NTempest;

C4Plane::C4Plane(const C3Vector &a2, const C3Vector &a3, const C3Vector &a4) {
    this->normal.x = 0.0;
    this->normal.y = 0.0;
    this->normal.z = 0.0;
    this->distance = 0.0f;
    this->From3Pos(a2, a3, a4);
}

C4Plane::C4Plane(const C3Vector &normal, float distance)
    : normal(normal), distance(distance) {}

void C4Plane::From3Pos(const C3Vector &a2, const C3Vector &a3, const C3Vector &a4) {
    float v5 = a4.z - a2.z;
    float v7 = a4.y - a2.y;
    float v8 = a4.x - a2.x;
    float v9 = a3.z - a2.z;
    float v10 = a3.y - a2.y;
    float v11 = a3.x - a2.x;
    this->normal.z = (float) (v7 * v11) - (float) (v8 * v10);
    this->normal.y = (float) (v8 * v9) - (float) (v11 * v5);
    this->normal.x = (float) (v5 * v10) - (float) (v7 * v9);
    this->normal.Normalize();
    this->distance = -(float) ((float) ((float) (this->normal.x * a2.x) + (float) (this->normal.y * a2.y))
                               + (float) (this->normal.z * a2.z));
}

float C4Plane::Dot(const C3Vector &v) const {
    return this->normal.x * v.x + this->normal.y * v.y + this->normal.z * v.z + this->distance;
}

float C4Plane::Distance(const C3Vector &v) const {
    return fabsf(this->Dot(v));
}

void C4Plane::Normalize() {
    float mag = this->normal.Mag();
    if (mag > 1e-6f) {
        float invMag = 1.0f / mag;
        this->normal.x *= invMag;
        this->normal.y *= invMag;
        this->normal.z *= invMag;
        this->distance *= invMag;
    }
}

C3Vector C4Plane::GetNormal() const {
    return this->normal;
}

float C4Plane::GetDistance() const {
    return this->distance;
}
