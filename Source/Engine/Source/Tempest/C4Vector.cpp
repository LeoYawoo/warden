#include "C4Vector.h"
#include <cmath>

using namespace Tempest;

C4Vector::C4Vector() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

C4Vector::C4Vector(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {}

float C4Vector::SquaredMag() const {
    return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

float C4Vector::Mag() const {
    return sqrtf(this->SquaredMag());
}

float C4Vector::Dot(const C4Vector &v) const {
    return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
}

C4Vector *C4Vector::operator/=(float div) {
    this->x = this->x / div;
    this->y = this->y / div;
    this->z = this->z / div;
    this->w = this->w / div;
    return this;
}

C4Vector *C4Vector::Normalize() {
    float v2;
    v2 = 1.0
         / sqrt((float) ((float) ((float) ((float) (this->x * this->x) + (float) (this->y * this->y))
                                  + (float) (this->z * this->z))
                         + (float) (this->w * this->w)));
    this->x = this->x * v2;
    this->y = v2 * this->y;
    this->z = v2 * this->z;
    this->w = v2 * this->w;
    return this;
}

C4Vector C4Vector::operator+(const C4Vector &v) const {
    return C4Vector(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}

C4Vector C4Vector::operator-(const C4Vector &v) const {
    return C4Vector(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}

C4Vector C4Vector::operator*(float s) const {
    return C4Vector(this->x * s, this->y * s, this->z * s, this->w * s);
}

C4Vector Tempest::operator*(float s, const C4Vector &v) {
    return v * s;
}