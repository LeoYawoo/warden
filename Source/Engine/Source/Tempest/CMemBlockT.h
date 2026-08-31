#pragma once

#include "CMemBlock.h"
#include "CDynParms.h"

namespace Tempest {

    template<typename T>
    class CMemBlockT : public CMemBlock {
    public:
        CMemBlockT(CDynParms const &a2, int a3, const char *a4, int a5) : CMemBlock(a2, a3, a4, a5) {}

        virtual ~CMemBlockT() {}

        virtual void Release() {
            this->~CMemBlockT();
            DeallocateMemoryEx(this);
        }
    };
}



