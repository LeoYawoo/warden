#include "C2Vector.h"
#include <cmath>

using namespace NTempest;

C2Vector::C2Vector() {
    x = 0.0f;
    y = 0.0f;
}

C2Vector::C2Vector(float x, float y) : x(x), y(y) {}

bool C2Vector::operator==(const C2Vector &v) const {
    return this->x == v.x && this->y == v.y;
}

bool C2Vector::operator!=(const C2Vector &v) const {
    return !(*this == v);
}

float C2Vector::SquaredMag() const {
    return this->x * this->x + this->y * this->y;
}

float C2Vector::Mag() const {
    return sqrtf(this->SquaredMag());
}

float C2Vector::Dot(const C2Vector &v) const {
    return this->x * v.x + this->y * v.y;
}

void C2Vector::FromAxisAngle(float value) {
    x = sinf(value);
    y = cosf(value);
}

float C2Vector::AxisAngle() {
    return AxisAngle_(Mag());
}

float C2Vector::AxisAngle_(float a2) {
    long double result;
    if (fabs(a2) < 0.00000023841858)
        return 0.0;
    result = acosf(this->x / a2);
    if (this->y < 0.0) {
        return (float) (6.2831855 - result);
    }
    return result;
}

C2Vector C2Vector::operator+(const C2Vector &v) const {
    return C2Vector(this->x + v.x, this->y + v.y);
}

C2Vector C2Vector::operator-(const C2Vector &v) const {
    return C2Vector(this->x - v.x, this->y - v.y);
}

C2Vector C2Vector::operator*(float s) const {
    return C2Vector(this->x * s, this->y * s);
}

C2Vector C2Vector::operator/(float s) const {
    float inv = 1.0f / s;
    return C2Vector(this->x * inv, this->y * inv);
}

C2Vector& C2Vector::operator+=(const C2Vector &v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

C2Vector& C2Vector::operator-=(const C2Vector &v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

C2Vector& C2Vector::operator*=(float s) {
    this->x *= s;
    this->y *= s;
    return *this;
}

C2Vector NTempest::operator*(float s, const C2Vector &v) {
    return v * s;
}