#pragma once

#include <cstdint>

namespace Tempest {
    class C2iVector {
    public:
        C2iVector();

        C2iVector(int32_t x, int32_t y);

    public:
        int32_t x;
        int32_t y;
    };
}

