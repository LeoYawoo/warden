#pragma once

#include "CPresenceTagged.h"
#include "CRandom.h"

namespace Tempest {
    template <typename T>
    class CLinkedList {
    public:
        int  Insert(int a1, int a2)
        {
            int result;

            *(uint32_t *)(a2 + 4) = a1;
            *(uint32_t *)(a2 + 8) = *(uint32_t *)(a1 + 8);
            result = *(uint32_t *)(a1 + 8);
            if ( result )
                *(uint32_t *)(result + 4) = a2;
            *(uint32_t *)(a1 + 8) = a2;
            return result;
        }

        void  ~CLinkedList(Ipse::CRlAgentDef *a1)
        {
            Ipse::CRlAgentDef::~CRlAgentDef(a1);
        }

        int * CLinkedList(Ipse::CRlAgentDef *a1)
        {
            Ipse::CRlAgentDef::CRlAgentDef(a1);
            return result;
        }

        virtual const char *sub_83A658()
        {
            return "RlAgentDef";
        }

        virtual int  sub_83B200(int a1)
        {
            int v1;

            v1 = sub_2EE210();
            return CLinkedNodeCache<Ipse::CRlAgentDef>::Dispose(v1, a1);
        }

        virtual ~CLinkedList(Ipse::CRlAgentDef *a1)
        {
            Ipse::CRlAgentDef::~CRlAgentDef(a1);
        }

        virtual int  sub_840810(Ipse::CRlAgentDef *a1)
        {
            Ipse::CRlAgentDef::~CRlAgentDef(a1);
            return DeallocateMemoryEx((TRefCnt *)a1);
        }

        virtual int  sub_2EE1D2(int a1, int a2)
        {
            sub_300E38(a1, a2);
            return Insert(unk_D6E420 + 604, a1);
        }

        virtual int  sub_2ED968(uint32_t *a1, int a2)
        {
            int v2;
            int v3;

            a1[19] |= 0x1000000u;
            v2 = a1[1];
            v3 = a1[2];
            if ( v2 )
                *(uint32_t *)(v2 + 8) = v3;
            if ( v3 )
                *(uint32_t *)(v3 + 4) = v2;
            a1[1] = 0;
            a1[2] = 0;
            sub_2ED5D0(a1, a2);
            if ( a1[73] )
                CDynTable<CPresenceData>::Remove(a1 + 66, 0, a1[73]);
            return sub_301A0A(a1, a2);
        }

        virtual void sub_839984()
        {
            ;
        }

        virtual void sub_83998C()
        {
            ;
        }

        virtual void sub_839994()
        {
            ;
        }

        virtual void sub_83999C()
        {
            ;
        }

        virtual int  sub_2EDFC6(int a1, CDataStore *a2)
        {
            sub_3011FE(a1, a2);
            return operator<<(a2, a1 + 264);
        }

        virtual int  sub_2EE12E(int a1, CDataStore *a2)
        {
            sub_30109C(a1, a2);
            operator>>(a2, a1 + 264);
            return Insert(unk_D6E420 + 604, a1);
        }

        virtual void sub_83A558()
        {
            ;
        }

        virtual void sub_83A560()
        {
            ;
        }

        virtual void sub_83A568()
        {
            ;
        }

        virtual void sub_83A570()
        {
            ;
        }

        virtual int  sub_3012A4(int a1, unsigned int a2, unsigned int *a3)
        {
            int v3;
            unsigned int *v5;
            unsigned int *v6;
            unsigned int *v7;
            unsigned int *v8;
            unsigned int *v9;
            unsigned int *v10;

            sub_2FAA08(a1, a2, v5);
            CuRandom::checksumr_(a1 + 68);
            CRandom::checksum32_(*(CRandom **)(a1 + 72), a2, v6);
            v3 = *(uint32_t *)(a1 + 48);
            if ( v3 )
            {
                CRandom::checksum32_(*(CRandom **)(v3 + 20), a2, v7);
                CRandom::checksum32_(*(CRandom **)(v3 + 24), a2, v8);
                CRandom::checksum32_(*(CRandom **)(v3 + 20), a2, v9);
                CRandom::checksum32_(*(CRandom **)(v3 + 24), a2, v10);
            }
            return CRandom::checksum32_(*(CRandom **)(a1 + 76), a2, a3);
        }

        virtual int  sub_300E78(int a1, int a2)
        {
            char v2;
            int result;
            int v4;
            char v5;
            char v6;

            CPresenceTagged::Checklog(a1, a2);
            sub_30052C(a2, "", v5);
            sub_30052C(a2, "[PrRe]", v6);
            v2 = sub_3005CA(a1 + 68, 1, -1);
            result = sub_30052C(a2, "\tdlt[%s] uid[%u] opt[0x%X]", v2);
            v4 = *(uint32_t *)(a1 + 48);
            if ( v4 )
            {
                sub_30052C(a2, "\talph t[%u] b[%u]", *(uint32_t *)(v4 + 20));
                result = sub_30052C(a2, "\tbeta t[%u] b[%u]", *(uint32_t *)(v4 + 20));
            }
            return result;
        }

        virtual void sub_83A578()
        {
            ;
        }

        virtual uint32_t * sub_3016AC(uint32_t *a1, int a2)
        {
            uint32_t *result;
            int v3;
            int v4;

            if ( a1[8] == a2 )
                return (uint32_t *)(*(int ( **)(uint32_t *, uint32_t))(*a1 + 20))(a1, 0);
            v3 = a1[19] | 0x800000;
            a1[19] = v3;
            v4 = *(uint32_t *)(a2 + 28);
            if ( (v3 & 0x400) != 0 )
            {
                sub_300D84(a1, 1584621927, *(uint32_t *)(a2 + 28));
                v3 = a1[19];
            }
            if ( (v3 & 0x100) != 0 )
            {
                sub_301496(a1, 1584621927, v4, 0);
                v3 = a1[19];
            }
            if ( (v3 & 0x200) != 0 )
                sub_300F60(a1, 1584621927, v4, 0);
            if ( a2 == a1[7] && (*(_BYTE *)(a2 + 16) & 1) == 0 )
                sub_30164C(a1);
            result = a1 + 19;
            a1[19] &= 0xFF7FFFFF;
            return result;
        }
    };
}


