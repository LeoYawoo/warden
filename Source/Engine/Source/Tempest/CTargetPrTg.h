#pragma once

#include <cstdint>
#include "CPresenceTagged.h"

namespace Tempest {
    class CTargetPrTg {
    public:
        CTargetPrTg(CPresenceTagged *a2, int a3) {
            this->a3 = 0;
            this->SetTarget(a2);
            this->a3 = a3;
        }

        void SetTarget(CPresenceTagged *a2) {
            if (a2) {
                this->a1 = a2->a6;
                this->a2 = a2->a7;
            } else {
                this->a2 = -1;
                this->a1 = -1;
            }
        }

    public:
        int a1;
        int a2;
        int a3;
    };
}



