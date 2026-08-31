#pragma once

#include "C3Vector.h"

namespace Tempest {
    class C4Plane {
    public:
        C4Plane() : normal(0.0f, 0.0f, 0.0f), distance(0.0f) {}

        C4Plane(const C3Vector &a2, const C3Vector &a3, const C3Vector &a4);

        C4Plane(const C3Vector &normal, float distance);

        void From3Pos(const C3Vector &a2, const C3Vector &a3, const C3Vector &a4);

        float Dot(const C3Vector &v) const;

        float Distance(const C3Vector &v) const;

        void Normalize();

        C3Vector GetNormal() const;

        float GetDistance() const;

    private:
        C3Vector normal;
        float distance;
    };
}


