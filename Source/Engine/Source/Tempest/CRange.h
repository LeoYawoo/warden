#pragma once

namespace Tempest {
    class CRange {
    public:
        CRange() {}

        CRange(float l,
               float h) : l(l), h(h) {
        }

    public:
        float l;
        float h;
    };
}
