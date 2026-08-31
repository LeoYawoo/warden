#pragma once

#include <cstdint>
#include "C33Matrix.h"
#include "C3uVector.h"
#include "Common/softfloat.h"


namespace Tempest {
    class C33uMatrix {
    public:
        C33uMatrix() {
            this->a0 = 1065353216;
            this->a1 = 0;
            this->a2 = 0;
            this->b0 = 0;
            this->b1 = 1065353216;
            this->b2 = 0;
            this->c0 = 0;
            this->c1 = 0;
            this->c2 = 1065353216;
        }

        C33uMatrix(uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, uint32_t a8,
                   uint32_t a9, uint32_t a10) {
            this->a0 = a2;
            this->a1 = a3;
            this->a2 = a4;
            this->b0 = a5;
            this->b1 = a6;
            this->b2 = a7;
            this->c0 = a8;
            this->c1 = a9;
            this->c2 = a10;
        }

        C33Matrix *asC33Matrix(C33Matrix *ret) {
            C3uVector v7(&this->a7, &this->a8, &this->a9);
            C3Vector v8;
            C3uVector v9(&this->a4, &this->a5, &this->a6);
            float v10;
            float v11;
            C3uVector v12(&this->a1, &this->a2, &this->a3);


            v7.asC3Vector(&v5);
            v6 = v5;
            v9.asC3Vector(&v4);
            v8 = v4;
            v12.asC3Vector(&v3);
            v10 = *(float *) &v3.y;
            v11 = *(float *) &v3.z;
            ret->a1 = v3.x;
            ret->a2 = v10;
            ret->a3 = v11;
            *(C3uVector *) &ret->a4 = v8;
            *(C3uVector *) &ret->a7 = v6;
            return ret;
        }


        C33uMatrix *Det() {
            softFloatMultiply(&v2);
            softFloatMultiply(v3);
            softFloatSubtract(v3, &v2);
            return this;
        }


    public:
        softfloat a0;
        softfloat a1;
        softfloat a2;
        softfloat b0;
        softfloat b1;
        softfloat b2;
        softfloat c0;
        softfloat c1;
        softfloat c2;
    };
}


