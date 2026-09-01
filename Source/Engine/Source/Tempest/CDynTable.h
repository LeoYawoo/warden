#pragma once

#include "CMemBlockT.h"
#include "CDynParms.h"

// Reverse engineered from Warcraft III binary
// CDynTable is a dynamic table implementation

namespace Tempest {
    template<typename T>
    class CDynTable : public CMemBlockT<T> {
    public:
        CDynTable(const CDynParms& parms) : m_parms(parms) {
        }

        virtual ~CDynTable() {
        }

        virtual void Release() {
            delete this;
        }

        // Grow the table
        bool Grow(size_t newSize, size_t growBy) {
            (void)newSize;
            (void)growBy;
            return true;
        }

        // Get parameters
        const CDynParms& GetParms() const {
            return m_parms;
        }

    private:
        CDynParms m_parms;
    };
}
