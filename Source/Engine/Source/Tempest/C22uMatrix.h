#pragma once

#include "Common/softfloat.h"

namespace Tempest {
    class C22uMatrix {
    public:
        C22uMatrix(const softfloat &a2, const softfloat &a3, const softfloat &a4, const softfloat &a5);

    public:
        softfloat a0;
        softfloat a1;
        softfloat b0;
        softfloat b1;
    };
}


