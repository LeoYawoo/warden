#pragma once


#include "C2iVector.h"
#include "CuMath.h"

namespace Tempest {
    class C2uVector {
    public:
        C2uVector(const C2iVector &that) {
            SoftFloatFromInt(&this->x, that.x);
            SoftFloatFromInt(&this->y, that.y);
        }

        C2uVector(unsigned int a2, unsigned int a3) {
            this->x = a2;
            this->y = a3;
        }

        C2uVector() {
            this->y = 0;
            this->x = 0;
        }

        C2uVector(const C2uVector &that) {
            this->x = that.x;
            this->y = that.y;
        }

        C2uVector *SquaredMag() {
            softFloatMultiply(v2);
            softFloatMultiply(v3);
            softFloatAdd(&this->x, (unsigned int *) v3, (unsigned int *) v2);
            return this;
        }

        C2uVector *Mag() {
            C2uVector v2;
            v2.SquaredMag();
            softFloatSqrt(this, v2);
            return this;
        }

        C2uVector *operator+=(C2uVector *that) {
            softFloatAdd(&a1, &this->x, &that->x);
            this->x = a1;
            softFloatAdd(v4, &this->y, &that->y);
            this->y = v4[0];
            return this;
        }

        C2uVector *SquaredDist(const C2uVector *that) {
            sub_D6070(this);
            return this;
        }

        C2uVector(unsigned int a2) {
            this->x = a2;
            this->y = a2;
        }

        int FromAxisAngle() {
            sub_D6B84(v3);
            softFloatMultiply(v2);
            sub_D6CE0(v5);
            softFloatMultiply(v4);
            *this = C2uVector((unsigned int *) v4, (unsigned int *) v2);
            return this;
        }

        C2uVector *operator/=(const int *a2) {
            Tempest::C2uVector v3;

            softFloatDiv(&v3.x, this, a2);
            this->x = v3.x;
            softFloatDiv(&v3.y, &this->y, a2);
            this->y = v3.y;
            return this;
        }

        C2uVector *AxisAngle() {
            C2uVector v2;

            v2.Mag();
            sub_6383EC(this);
            return this;
        }

        C2uVector *operator-(unsigned int *a2) {
            v3 = a2[1] + 0x80000000;
            v4[0] = *a2 + 0x80000000;
            *this = C2uVector(v4, &v3);
            return this;
        }

        float *AngleToAxisAngle(float *a1, float *a2) {
            v3[0] = *(unsigned int *) a2;
            v3[1] = v3[0] & 0x7FFFFFFF;
            if (COERCE_FLOAT(v3[0] & 0x7FFFFFFF) >= *(float *) &dword_F69FA0) {
                sub_D5BEA(v4);
                *(float *) v3 = v4[0];
            }
            if (flt_F6A138 <= *(float *) v3)
                *a1 = *(float *) v3;
            else
                softFloatAdd((unsigned int *) a1, v3, (unsigned int *) &dword_F69FA0);
            return a1;
        }

        C2uVector *Scale() {
            CuMath::hypotinv_(v3);
            softFloatMultiply(v2);
            softFloatMultiply(v4);
            this->x = v4;
            softFloatMultiply(v5);
            this->y = v5;
            return this;
        }

        C2uVector asC2Vector() {
            return *this;
        }

        C2uVector *Dot(const C2uVector *a2, const C2uVector *a3) {
            softFloatMultiply(v4);
            softFloatMultiply(v5);
            softFloatAdd(&this->x, (unsigned int *) v5, (unsigned int *) v4);
            return this;
        }

        C2uVector *Normalize() {
            CuMath::hypotinv_(v2);
            softFloatMultiply(&v3);
            this->x = v3;
            softFloatMultiply(v4);
            this->y = v4[0];
            return this;
        }

        C2uVector *operator-=(float *a3) {
            softFloatSubtract(&a1, (float *) &this->x, a3);
            this->x = a1;
            softFloatSubtract(v4, (float *) &this->y, a3 + 1);
            this->y = v4[0];
            return this;
        }

        C2uVector *operator*=() {
            softFloatMultiply(&v2);
            this->x = v2;
            softFloatMultiply(v3);
            this->y = v3;
            return this;
        }

    public:
        unsigned int x;
        unsigned int y;
    };
}


