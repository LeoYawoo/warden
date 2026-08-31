#pragma once

#include <ntdef.h>
#include "CDynTable.h"
#include "CPrRgEntry.h"
#include "CDynParms.h"

namespace Tempest {
    class CPresenceReg {
    public:
        CPresenceReg(CDynParms const &params) : m_a1(params, 0, 0, 0), m_a2(params, 0, 0, 0) {
            this->filed_10 = -1;
            this->filed_11 = -1;
            this->filed_12 = 0;
            this->filed_13 = 0;
            this->filed_14 = 0;
            this->filed_15 = 0;
            this->filed_16 = 0;
        }

        ~CPresenceReg() {
        }


        bool IsAssociated(int a2) {
            Tempest::CPresenceReg *p_a2;
            unsigned int v3;

            p_a2 = this;
            v3 = a2;
            if (a2 < 0) {
                v3 = a2 & 0x7FFFFFFF;
                p_a2 = (Tempest::CPresenceReg *) &this->m_a2;
            }
            return v3 < p_a2->m_a1.filed_28 && *(uintptr_t *) (p_a2->m_a1.a5 + 8 * v3) == -2;
        }

        int Presence(int a2) {
            int a5;

            if (a2 >= 0)
                a5 = this->m_a1.a5;
            else
                a5 = this->m_a2.a5;
            return *(uintptr_t *) (a5 + 8 * a2 + 4);
        }

        unsigned int PredictTag(int a2) {
            int filed_11;
            unsigned int result;

            if (a2) {
                filed_11 = this->filed_11;
                if (filed_11 == -1)
                    filed_11 = this->m_a2.filed_28;
                return filed_11 | 0x80000000;
            } else {
                result = this->filed_10;
                if (result == -1)
                    return this->m_a1.filed_28;
            }
            return result;
        }

    public:
        CDynTable<CPrRgEntry> m_a1;
        CDynTable<CPrRgEntry> m_a2;
        int filed_10;
        int filed_11;
        int filed_12;
        int filed_13;
        int filed_14;
        int filed_15;
        int filed_16;
    };
}



