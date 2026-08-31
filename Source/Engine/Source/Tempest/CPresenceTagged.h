#pragma once

#include "CPresenceReg.h"
#include "CThreadData.h"

namespace Tempest {
    class CPresenceTagged: public CPresence {
    public:
        int  TagsToPresence(unsigned int a2)
        {
            int result;

            if ( !CPresenceReg::IsAssociated((CPresenceReg *)dword_D6E460, (unsigned int)this)
                 || (result = CPresenceReg::Presence((CPresenceReg *)dword_D6E460, (unsigned int)this),
                    *(uint32_t *)(result + 24) != a2) )
            {
                result = 0;
            }
            return result;
        }

         ~CPresenceTagged()
        {
        }

        CPresenceTagged()
        {
            *((uint32_t *)this + 1) = 0;
            *((uint32_t *)this + 2) = 0;
            *(uint32_t *)this = &`vtable for'CPresence + 2;
                                            *((uint32_t *)this + 3) = 0;
            *((uint32_t *)this + 4) = 0;
            *(uint32_t *)this = &`vtable for'CPresenceTagged + 2;
                                            *((uint32_t *)this + 5) = -1;
            *((uint32_t *)this + 6) = -1;

        }

        int  AssociateForcedTags(int a1, int a2, int a3)
        {
            int result;

            result = a1;
            *(uint32_t *)(a1 + 36) = a2;
            *(uint32_t *)(a1 + 40) = a3;
            return result;
        }

        int  Checklog(int a1, int a2)
        {
            char v3;

            sub_30052C(a2, "", v3);
            return sub_30052C(a2, "[PrTg] t[%u] b[%u]", *(uint32_t *)(a1 + 20));
        }

        int  TouchBirthTag()
        {
            int result;
            int v2;

            result = dword_D6E460;
            if ( *((int *)this + 5) >= 0 )
            {
                v2 = *(uint32_t *)(dword_D6E460 + 80);
                *(uint32_t *)(dword_D6E460 + 80) = v2 + 1;
            }
            else
            {
                v2 = *(uint32_t *)(dword_D6E460 + 84);
                *(uint32_t *)(dword_D6E460 + 84) = v2 + 1;
            }
            *((uint32_t *)this + 6) = v2;
            return result;
        }
    public:
        int a2;
        int a3;
        int a4;
        int a5;
        int a6;
        int a7;
    };
}



