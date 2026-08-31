#pragma once


namespace Tempest {
    class C33Matrix;

    class C3Vector;

    C33Matrix operator*(const C33Matrix &l, float a);

    C33Matrix operator/(const C33Matrix &l, float a);

    C33Matrix operator*(const C33Matrix &l, const C33Matrix &r);

    C3Vector operator*(const C33Matrix &l, const C3Vector &r);

    class C33Matrix {
    public:
        // Static functions
        static C33Matrix Identity();

        // Member functions
        C33Matrix();

        C33Matrix(float a0, float a1, float a2, float b0, float b1, float b2, float c0, float c1, float c2);

        C33Matrix Adjoint() const;

        float Determinant() const;

        C33Matrix Inverse(float det) const;

        C33Matrix Transpose() const;


    public:
        float a0;
        float a1;
        float a2;
        float b0;
        float b1;
        float b2;
        float c0;
        float c1;
        float c2;
    };


}


