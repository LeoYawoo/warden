#pragma once

#include "C3Vector.h"
#include "C2uVector.h"
#include "CuMath.h"

namespace Tempest {
    class C3uVector {
    public:
        C3Vector *asC3Vector(C3Vector &ret) {
            ret.x = *(float *) &this->x;
            ret.y = *(float *) &this->y;
            ret.z = *(float *) &this->z;
            return &ret;
        }

        C3uVector(int *a) {
            SoftFloatFromInt(x, *a);
            SoftFloatFromInt(y, a[1]);
            SoftFloatFromInt(z, a[2]);
        }

        C3uVector *SquaredMag() {
            softFloatMultiply(v2);
            softFloatMultiply(v4);
            softFloatMultiply(v5);
            softFloatAdd((unsigned int *) v3, (unsigned int *) v5, (unsigned int *) v4);
            softFloatAdd(&this->x, (unsigned int *) v3, (unsigned int *) v2);
            return this;
        }

        C3uVector(const C3uVector &that) {
            this->x = that.x;
            this->y = that.y;
            this->z = that.z;
        }

        C3uVector(unsigned int a2, unsigned int a3, unsigned int a4) {
            this->x = a2;
            this->y = a3;
            this->z = a4;
        }

        C3uVector() {
            this->z = 0;
            this->y = 0;
            this->x = 0;
        }

        C3uVector(const C2uVector &that) {
            this->x = that.x;
            this->y = that.y;
            this->z = 0;
        }

        C3uVector *Mag() {
            C3uVector v2;
            v2.SquaredMag();
            softFloatSqrt(this, v2);
            return this;
        }

        C3uVector *operator+=(C3uVector *that) {
            softFloatAdd(&v3, &this->x, &that->x);
            this->x = v3;
            softFloatAdd(&v4, &this->y, &that->y);
            this->y = v4;
            softFloatAdd((unsigned int *) v5, &this->z, &that->z);
            this->z = v5[0];
            return this;
        }

        C3uVector *Scale() {
            CuMath::hypotinv_(v3);
            softFloatMultiply(v2);
            softFloatMultiply(&v4);
            this->x = v4;
            softFloatMultiply(&v5);
            this->y = v5;
            softFloatMultiply(v6);
            this->z = v6[0];
            return this;
        }

        C3uVector *Normalize() {
            CuMath::hypotinv_(v2);
            softFloatMultiply(&v3);
            this->x = v3;
            softFloatMultiply(&v4);
            this->y = v4;
            softFloatMultiply(v5);
            this->z = v5[0];
            return this;
        }

        C3uVector *operator*=() {
            softFloatMultiply(&v2);
            this->x = v2;
            softFloatMultiply(&v3);
            this->y = v3;
            softFloatMultiply(v4);
            this->z = v4[0];
            return this;
        }

    public:
        unsigned int x;
        unsigned int y;
        unsigned int z;
    };
}


