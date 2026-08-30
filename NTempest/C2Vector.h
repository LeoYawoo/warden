#pragma once


namespace NTempest {
    class C2Vector {
    public:
        C2Vector();

        C2Vector(float x, float y);

        bool operator==(const C2Vector &v) const;

        bool operator!=(const C2Vector &v) const;

        float SquaredMag() const;

        float Mag() const;

        float Dot(const C2Vector &v) const;

        void FromAxisAngle(float value);

        float AxisAngle();

        float AxisAngle_(float a2);

        C2Vector operator+(const C2Vector &v) const;

        C2Vector operator-(const C2Vector &v) const;

        C2Vector operator*(float s) const;

        C2Vector operator/(float s) const;

        C2Vector& operator+=(const C2Vector &v);

        C2Vector& operator-=(const C2Vector &v);

        C2Vector& operator*=(float s);

    public:
        float x;
        float y;
    };

    C2Vector operator*(float s, const C2Vector &v);
}


