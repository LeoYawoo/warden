#pragma once

#include "CMemBlockT.h"
#include "CDynParms.h"

namespace Tempest {
    template<typename T>
    class CDynTable : public CMemBlockT<T> {
    public:
        CDynTable(CDynParms const &a2, int a3, const char *a4, int a5) : CMemBlockT<T>(a2, a, a4, a5) {}

        virtual ~CDynTable() {}

        virtual void Release() {
            this->~CMemBlockT();
            DeallocateMemoryEx(this);
        }
    };
}


