#pragma once

#include "CRndSeed.h"
#include "Common/softfloat.h"

namespace Tempest {
    class CuRange {
    public:
        CuRange(const softfloat &min, const softfloat &max) {
            this->min = min;
            this->max = max;
        }

        CuRange *ClampClosed(const softfloat &a2, const softfloat &a3) {
            softfloat v3;

            v3 = a2;
            if (a2 <= a3) {
                v3 = a2 + 1;
                if (a3 <= a2[1])
                    v3 = a3;
            }
            this->min = v3;
            return this;
        }

        CuRange *Value(CRndSeed *a2) {
            char v2[4];
            char v3[12];

            softFloatSubtract(v3);
            sub_5E602C(v2);
            softFloatAdd(this);
            return this;
        }

        bool InClosedRange(const softfloat &a2) {
            return a2 >= this->min && this->max >= a2;
        }

    public:
        softfloat min;
        softfloat max;
    };
}


