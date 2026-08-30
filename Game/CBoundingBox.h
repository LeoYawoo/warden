#pragma once

#include "NTempest/CRange.h"
#include "NTempest/C3Vector.h"

using namespace NTempest;

class CBoundingBox {
public:
    // Member variables
    CRange x;
    CRange y;
    CRange z;

    // Constructors
    CBoundingBox() = default;

    CBoundingBox(const C3Vector &min, const C3Vector &max)
        : x(min.x, max.x), y(min.y, max.y), z(min.z, max.z) {}

    CBoundingBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
        : x(minX, maxX), y(minY, maxY), z(minZ, maxZ) {}

    // Getters
    C3Vector GetMin() const { return C3Vector(x.l, y.l, z.l); }
    C3Vector GetMax() const { return C3Vector(x.h, y.h, z.h); }
    C3Vector GetCenter() const {
        return C3Vector(
            (x.l + x.h) * 0.5f,
            (y.l + y.h) * 0.5f,
            (z.l + z.h) * 0.5f
        );
    }

    C3Vector GetSize() const {
        return C3Vector(
            x.h - x.l,
            y.h - y.l,
            z.h - z.l
        );
    }

    float GetVolume() const {
        return (x.h - x.l) * (y.h - y.l) * (z.h - z.l);
    }

    float GetSurfaceArea() const {
        float dx = x.h - x.l;
        float dy = y.h - y.l;
        float dz = z.h - z.l;
        return 2.0f * (dx * dy + dy * dz + dz * dx);
    }

    // Containment tests
    bool Contains(const C3Vector &point) const {
        return point.x >= x.l && point.x <= x.h &&
               point.y >= y.l && point.y <= y.h &&
               point.z >= z.l && point.z <= z.h;
    }

    bool Contains(const CBoundingBox &other) const {
        return other.x.l >= x.l && other.x.h <= x.h &&
               other.y.l >= y.l && other.y.h <= y.h &&
               other.z.l >= z.l && other.z.h <= z.h;
    }

    bool Intersects(const CBoundingBox &other) const {
        return x.l <= other.x.h && x.h >= other.x.l &&
               y.l <= other.y.h && y.h >= other.y.l &&
               z.l <= other.z.h && z.h >= other.z.l;
    }

    // Expansion
    void Expand(const C3Vector &point) {
        if (point.x < x.l) x.l = point.x;
        if (point.x > x.h) x.h = point.x;
        if (point.y < y.l) y.l = point.y;
        if (point.y > y.h) y.h = point.y;
        if (point.z < z.l) z.l = point.z;
        if (point.z > z.h) z.h = point.z;
    }

    void Expand(const CBoundingBox &other) {
        if (other.x.l < x.l) x.l = other.x.l;
        if (other.x.h > x.h) x.h = other.x.h;
        if (other.y.l < y.l) y.l = other.y.l;
        if (other.y.h > y.h) y.h = other.y.h;
        if (other.z.l < z.l) z.l = other.z.l;
        if (other.z.h > z.h) z.h = other.z.h;
    }

    void ExpandByMargin(float margin) {
        x.l -= margin;
        x.h += margin;
        y.l -= margin;
        y.h += margin;
        z.l -= margin;
        z.h += margin;
    }

    // Reset
    void Reset() {
        x.l = x.h = 0.0f;
        y.l = y.h = 0.0f;
        z.l = z.h = 0.0f;
    }

    // Equality
    bool operator==(const CBoundingBox &other) const {
        return x.l == other.x.l && x.h == other.x.h &&
               y.l == other.y.l && y.h == other.y.h &&
               z.l == other.z.l && z.h == other.z.h;
    }

    bool operator!=(const CBoundingBox &other) const {
        return !(*this == other);
    }
};
