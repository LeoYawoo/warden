#pragma once


namespace Tempest {
    class C4Vector {
    public:
        C4Vector();

        C4Vector(float x, float y, float z, float w);

        float Mag() const;

        float SquaredMag() const;

        float Dot(const C4Vector &v) const;

        C4Vector *operator/=(float div);

        C4Vector *Normalize();

        C4Vector operator+(const C4Vector &v) const;

        C4Vector operator-(const C4Vector &v) const;

        C4Vector operator*(float s) const;

    public:
        float x;
        float y;
        float z;
        float w;
    };

    C4Vector operator*(float s, const C4Vector &v);
}


