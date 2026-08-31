#pragma once

#include "C4Vector.h"
#include "C4Quaternion.h"
#include "C3Vector.h"

namespace Tempest {
    class C44Matrix;

    C44Matrix operator*(const C44Matrix &l, float a);

    C44Matrix operator*(const C44Matrix &l, const C44Matrix &r);

    class C44Matrix {
    public:
        // Static functions
        static C44Matrix Identity();

        static C44Matrix RotationAroundZ(float angle);

        static C44Matrix RotationAroundX(float angle);

        static C44Matrix RotationAroundY(float angle);

        static C44Matrix LookAt(const C3Vector &eye, const C3Vector &target, const C3Vector &up);

        static C44Matrix Perspective(float fov, float aspect, float nearPlane, float farPlane);

        static C44Matrix Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

        // Member functions
        C44Matrix();

        C44Matrix(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1,
                  float c2, float c3, float d0, float d1, float d2, float d3);

        C44Matrix(const C4Quaternion &rotation);

        C44Matrix Adjoint() const;

        float Determinant() const;

        C44Matrix Inverse(float det) const;

        void RotateAroundZ(float angle);

        void RotateAroundX(float angle);

        void RotateAroundY(float angle);

        void Scale(const C3Vector &scale);

        void Scale(float scale);

        void Translate(const C3Vector &move);

        C44Matrix Transpose() const;

    public:
        float a0;
        float a1;
        float a2;
        float a3;
        float b0;
        float b1;
        float b2;
        float b3;
        float c0;
        float c1;
        float c2;
        float c3;
        float d0;
        float d1;
        float d2;
        float d3;
    };
}


