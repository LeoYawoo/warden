#pragma once


namespace Tempest {
    class CImVector;

    class C44Matrix;

    class C3Vector {
    public:
        C3Vector();

        C3Vector(float x, float y, float z);

        C3Vector(const CImVector &color);

        bool operator==(const C3Vector &v) const;

        bool operator!=(const C3Vector &v) const;

        C3Vector &operator*=(float a);

        C3Vector &operator+=(const C3Vector &v);

        C3Vector &operator-=(const C3Vector &v);

        float SquaredMag() const;

        float Mag() const;

        float Dot(const C3Vector &v) const;

        C3Vector Cross(const C3Vector &v) const;

        C3Vector *ProjectionOnPlane(const C3Vector &a2, const C3Vector &a3);

        C3Vector *NearestOnPlane(const C3Vector &a2, const C3Vector &a3, const C3Vector &a4);

        void Normalize();

        bool IsUnit();

        C3Vector *operator/=(float a2);

    public:
        float x;
        float y;
        float z;
    };

    C3Vector operator+(const C3Vector &l, const C3Vector &r);

    C3Vector operator-(const C3Vector &l, const C3Vector &r);

    C3Vector operator*(const C3Vector &l, float s);

    C3Vector operator*(float s, const C3Vector &r);

    C3Vector operator/(const C3Vector &l, float s);

    C3Vector operator*(const C3Vector &l, const C44Matrix &r);
}


