#pragma once

#include <cstdint>
#include <cmath>
#include "../Tempest/C3Vector.h"
#include "../Tempest/C2Vector.h"
#include "../Tempest/CImVector.h"

using namespace Tempest;

// 4-byte unsigned integer type
struct ubyte4 {
    union {
        uint8_t v[4];
        uint32_t u;
    };

    ubyte4() : u(0) {}
    ubyte4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : v{a, b, c, d} {}
    explicit ubyte4(uint32_t val) : u(val) {}

    uint8_t &operator[](size_t i) { return v[i]; }
    const uint8_t &operator[](size_t i) const { return v[i]; }
};

// Vertex structure for PBNT2 format
struct CGxVertexPBNT2 {
    C3Vector position;
    ubyte4 bw;  // blend weights
    ubyte4 bi;  // blend indices
    C3Vector normal;
    C2Vector texCoord0;
    C2Vector texCoord1;
};

// Vertex structure for PCT format (Position, Color, TexCoord)
struct CGxVertexPCT {
    C3Vector p;
    CImVector c;
    C2Vector tc[2];
};

struct fixed16 {
    int16_t n;

    // Constructors
    fixed16() : n(0) {}
    explicit fixed16(int16_t value) : n(value) {}
    explicit fixed16(float value) : n(static_cast<int16_t>(value * 32767.0f)) {}

    // Conversion operators
    explicit operator float() const;

    // Arithmetic operators
    fixed16 operator+(const fixed16 &other) const {
        return fixed16(static_cast<int16_t>(n + other.n));
    }

    fixed16 operator-(const fixed16 &other) const {
        return fixed16(static_cast<int16_t>(n - other.n));
    }

    fixed16 operator*(const fixed16 &other) const {
        return fixed16(static_cast<int16_t>((static_cast<int32_t>(n) * other.n) >> 15));
    }

    fixed16 operator/(const fixed16 &other) const {
        if (other.n == 0) return fixed16(static_cast<int16_t>(0));
        return fixed16(static_cast<int16_t>((static_cast<int32_t>(n) << 15) / other.n));
    }

    // Compound assignment operators
    fixed16 &operator+=(const fixed16 &other) {
        n += other.n;
        return *this;
    }

    fixed16 &operator-=(const fixed16 &other) {
        n -= other.n;
        return *this;
    }

    fixed16 &operator*=(const fixed16 &other) {
        n = static_cast<int16_t>((static_cast<int32_t>(n) * other.n) >> 15);
        return *this;
    }

    fixed16 &operator/=(const fixed16 &other) {
        if (other.n != 0) {
            n = static_cast<int16_t>((static_cast<int32_t>(n) << 15) / other.n);
        }
        return *this;
    }

    // Comparison operators
    bool operator==(const fixed16 &other) const { return n == other.n; }
    bool operator!=(const fixed16 &other) const { return n != other.n; }
    bool operator<(const fixed16 &other) const { return n < other.n; }
    bool operator>(const fixed16 &other) const { return n > other.n; }
    bool operator<=(const fixed16 &other) const { return n <= other.n; }
    bool operator>=(const fixed16 &other) const { return n >= other.n; }

    // Utility functions
    fixed16 Abs() const {
        return fixed16(static_cast<int16_t>(n < 0 ? -n : n));
    }

    fixed16 Clamp(const fixed16 &min, const fixed16 &max) const {
        if (n < min.n) return min;
        if (n > max.n) return max;
        return *this;
    }

    static fixed16 FromFloat(float value) {
        return fixed16(static_cast<int16_t>(value * 32767.0f));
    }

    static float ToFloat(fixed16 value) {
        return static_cast<float>(value.n) / 32767.0f;
    }
};

