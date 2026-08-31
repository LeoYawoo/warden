#pragma once

#include <cstdint>
#include "C2uVector.h"
#include "CRandSeed.h"
#include "CiRect.h"
#include "CRect.h"

namespace Tempest {
    class CuRect {
    public:
        CuRect() {
            this->maxx = 0;
            this->maxy = 0;
            this->minx = 0;
            this->miny = 0;
        }

        CuRect(unsigned int *miny, unsigned int *minx, unsigned int *maxy, unsigned int *maxx) {
            this->maxx = *miny;
            this->maxy = *minx;
            this->minx = *maxy;
            this->miny = *maxx;
        }

        CuRect(unsigned int *val) {
            this->miny = *val;
            this->minx = *val;
            this->maxy = *val;
            this->maxx = *val;
        }

        CuRect(const CuRect *that) {
            *this = *that;
        }

        CuRect(const CiRect *that) {
            SoftFloatFromInt(this);
            SoftFloatFromInt(&this->minx);
            SoftFloatFromInt(&this->maxy);
            SoftFloatFromInt(&this->maxx);
        }

        CuRect(const C2uVector *topLeft, const C2uVector *downRight) {
            this->miny = topLeft->y;
            this->minx = topLeft->x;
            this->maxy = downRight->y;
            this->maxx = downRight->x;
        }

        CuRect(const C2uVector *pos) {
            this->miny = pos->y;
            this->minx = pos->x;
            this->maxy = pos->y;
            this->maxx = pos->x;
        }

        bool Contains(const C2uVector *pos) {
            float v2;
            bool result = 0;
            if (*(float *) &pos->x > *(float *) &this->minx && *(float *) &this->maxx > *(float *) &pos->x) {
                v2 = *(float *) &pos->y;
                if (v2 > *(float *) &this->miny && *(float *) &this->maxy > v2)
                    return 1;
            }
            return result;
        }

        C2uVector *Center() {
            char v2[4];
            char v3[4];
            char v4[4];
            char v5[28];

            softFloatAdd(v3);
            softFloatMultiply(v2);
            softFloatAdd(v5);
            softFloatMultiply(v4);
            C2uVector *ret = new C2uVector(v4, v2);
            return ret;
        }

        CuRect *Intersect(CuRect *a2) {
            CuRect v4;

            Intersection(&v4, a2, a3);
            *a2 = v4;
            CuRect(a2);
            return this;
        }

        CuRect *Intersection(const CuRect *rect1, const CuRect *rect2) {
            const CuRect *v3;
            unsigned int *p_maxx;
            unsigned int *p_maxy;
            unsigned int *p_minx;
            int v8;

            v3 = rect2;
            p_maxx = &rect2->maxx;
            if (*(float *) &rect2->maxx > *(float *) &rect1->maxx)
                p_maxx = &rect1->maxx;
            v8 = (int) p_maxx;
            p_maxy = &rect2->maxy;
            if (*(float *) &rect2->maxy > *(float *) &rect1->maxy)
                p_maxy = &rect1->maxy;
            p_minx = &rect2->minx;
            if (*(float *) &rect1->minx > *(float *) &rect2->minx)
                p_minx = &rect1->minx;
            if (*(float *) &rect1->miny > *(float *) &rect2->miny)
                v3 = rect1;
            CuRect(this, (int) v3, (int) p_minx, (int) p_maxy, v8);
            return this;
        }

        bool NotEmpty() {
            return *(float *) &this->maxy > *(float *) &this->miny && *(float *) &this->maxx > *(float *) &this->minx;
        }

        int Offset(unsigned int *x, unsigned int *y) {
            softFloatAdd(&v3);
            this->miny = v3;
            softFloatAdd(&v4);
            this->minx = v4;
            softFloatAdd(&v5);
            this->maxy = v5;
            softFloatAdd(&v6);
            this->maxx = v6;
        }

        void Stretch(C2uVector *size) {
            softFloatAdd(&v3);
            this->miny = v3;
            softFloatAdd(&v4);
            this->minx = v4;
            softFloatSubtract(&v5);
            this->maxy = v5;
            softFloatSubtract(&v6);
            this->maxx = v6;
        }

        void Stretch(const int *x, const int *y) {
            softFloatAdd(&v4);
            this->miny = v4;
            softFloatAdd(&v5);
            this->minx = v5;
            softFloatSubtract(&v6);
            this->maxy = v6;
            softFloatSubtract(&v7);
            this->maxx = v7;
        }

        CuRect *ValueH(CRandSeed *seed) {
            softFloatSubtract(v4);
            sub_631BF4(v3);
            softFloatAdd(this);
            return this;
        }

        CuRect *ValueV(CRandSeed *seed) {
            softFloatSubtract(v4);
            sub_631BF4(v3);
            softFloatAdd(this);
            return this;
        }

        CRect *asCRect() {
            CRect result;
            result.minY = *(float *) &this->miny;
            result.minX = *(float *) &this->minx;
            result.maxY = *(float *) &this->maxy;
            result.maxX = *(float *) &this->maxx;
            return &result;
        }

    public:
        unsigned int miny;
        unsigned int minx;
        unsigned int maxy;
        unsigned int maxx;
    };
}



