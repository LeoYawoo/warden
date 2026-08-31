#pragma once


#include "CEntity.h"

namespace Tempest {
    class CSyncData : public CEntity {
    public:
        CSyncData() {
            this->a2 = 0;
            this->a3 = 0;
            this->a4 = "";
        }

        virtual ~CSyncData() {

        }

        virtual int Release() {
            return DeallocateMemoryEx(this);
        }

        virtual int sub_7A2E94() {
            return this->a2;
        }

        virtual CSyncData *Reset() {
            this->a2 = 0;
            this->a3 = 0;
            return this;
        }

        virtual void sub_7A2EB8() {
            ;
        }

        virtual int sub_7A2EC0(int a2) {
            char v2;
            char v4;

            sub_30052C(a2, "", v4);
            sub_30052C(a2, "[CSyncData] (%s)", this->a4);
            v2 = this->sub_7A2E94();
            return sub_30052C(a2, "\tcsum[%08X], count[%u]", v2);
        }

    public:
        int a2;
        int a3;
        char *a4;
    };
}



