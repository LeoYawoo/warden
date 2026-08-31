#pragma once

#include <cstdint>



namespace Tempest {
    class CRandom {
    public:
        int  uint32_(uint32_t *a1)
        {
            int v1;
            int v2;
            int v3;
            int v4;
            int v5;
            int v6;
            int v7;
            int v8;
            int v9;
            int v10;
            int v11;
            int result;
            int v13;
            int v14;
            int v15;

            v1 = HIBYTE(a1[1]);
            v2 = (unsigned __int8)BYTE2(a1[1]);
            v15 = (unsigned __int8)BYTE1(a1[1]);
            v3 = (unsigned __int8)a1[1];
            v4 = v1 + 184;
            v5 = v1 - 4;
            if ( v5 >= 0 )
                v4 = v5;
            v13 = v4;
            v6 = v2 + 200;
            v7 = v2 - 12;
            if ( v7 < 0 )
                v7 = v6;
            v8 = v15 - 24;
            if ( v15 - 24 < 0 )
                v8 = v15 + 212;
            v14 = v8;
            v9 = __ROR4__(*(int *)((char *)&dword_A7FC20 + v13), 31);
            v10 = v3 + 216;
            v11 = v3 - 28;
            if ( v11 < 0 )
                v11 = v10;
            result = *a1
                     + (*(int *)((char *)&dword_A7FC20 + v11) ^ __ROR4__(*(int *)((char *)&dword_A7FC20 + v14), 29) ^ __ROR4__(*(int *)((char *)&dword_A7FC20 + v7), 30) ^ v9);
            a1[1] = (((v13 << 8) | v7) << 16) | (v14 << 8) | v11;
            *a1 = result;
            return result;
        }

        int64_t  dice_(unsigned int a1, int a2)
        {
            int64_t result;

            LODWORD(result) = (a1 * (uint64_t)(unsigned int)uint32_(a2)) >> 32;
            HIDWORD(result) = 0;
            return result;
        }

        int  dice_(int a1, unsigned int a2, int a3)
        {
            int v3;
            unsigned int i;
            unsigned int v5;
            float v6;
            float v8;

            if ( a2 > 0x10 )
            {
                v5 = (a1 - 1) * a2;
                if ( (v5 & 0x80000000) != 0 )
                    v6 = (float)(v5 & 1 | (v5 >> 1)) + (float)(v5 & 1 | (v5 >> 1));
                else
                    v6 = (float)(int)v5;
                v8 = ((double ( *)(uint32_t, uint32_t, uint32_t))sub_3C9598)(v6 * 0.5, sqrtf(v6), a3);
                v3 = (int)(float)(v8 + 0.5);
                if ( v5 < v3 )
                    v3 = v5 & ~(v3 >> 31);
            }
            else
            {
                v3 = 0;
                for ( i = 0; i < a2; ++i )
                    v3 += dice_(a1, a3);
            }
            return v3;
        }

        int  checksum16_(CRandom *this, unsigned int a2)
        {
            int result;

            result = 31277 * (unsigned __int8)this;
            *(uint32_t *)a2 += (result ^ (unsigned __int8)this) + ((31277 * BYTE1(this)) ^ BYTE1(this));
            return result;
        }

        int  checksum32_(CRandom *this, unsigned int a2, unsigned int *a3)
        {
            unsigned int *v4;

            checksum16_((CRandom *)((unsigned int)this >> 16), a2, v4);
            return checksum16_(this, a2, a3);
        }

        int  checksum_(CRandom **a1, unsigned int a2, unsigned int *a3)
        {
            unsigned int *v4;

            checksum32_(*a1, a2, v4);
            return checksum32_(a1[1], a2, a3);
        }

        long double  lrealp_(int a1)
        {
            int v1;

            v1 = uint32_(a1);
            return 2.0 - COERCE_DOUBLE(__PAIR64__(v1 & 0xFFFFF | 0x3FF00000u, uint32_(a1)));
        }

        long double  lreal_(int a1)
        {
            int v1;

            v1 = uint32_(a1);
            return COERCE_DOUBLE(__PAIR64__(v1 & 0xFFFFF | 0x3FF00000u, uint32_(a1))) - 1.0;
        }

        long double  lreals_(int a1)
        {
            int v1;
            float v2;
            float v3;
            double v5;

            v1 = uint32_(a1);
            HIDWORD(v5) = v1 & 0xFFFFF | 0x3FF00000;
            LODWORD(v5) = uint32_(a1);
            v2 = v5;
            if ( v1 >= 0 )
                v3 = v2 - 2.0;
            else
                v3 = 2.0 - v2;
            return v3;
        }
    };
}



