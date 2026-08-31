#pragma once

#include "TSHashTable.h"

template<typename T, typename N>
class TSHashTable_P : public TSHashTable<T, N> {
public:
    TSHashTable_P()
    {
        this->field_18 = 0;
        this->field_19 = 0;
        this->field_20 = 0;
    }
    ~TSHashTable_P()
    {
        void* i = this->field_18;
        if (i!=nullptr) {
            DeallocateMemory(i);
        }
        this->field_18 = 0;
        this->field_19 = 0;
        this->field_20 = 0;

    }
    int New(int a2, int a3, int a4)
    {
        int v4; // eax

        v4 = IIntern( a2);
        return New(v4, a3, a4);
    }
    char *IIntern(const char *a2)
    {
        int v2; // eax
        int field_20; // edx
        _DWORD *MemoryWithInitialization; // eax
        _DWORD *field_19; // edx
        int v6; // esi
        int v8; // [esp+1Ch] [ebp-1Ch]

        v2 = sub_1A6B6((void *)a2) + 1;
        v8 = v2;
        if ( !this->field_19 || (field_20 = this->field_20, field_20 + v2 > 0x1FFF) )
        {
            MemoryWithInitialization = SMemAlloc(
                    0x2000u,
                    "../../../System/Storm/H/SAPIEXTEND.H",
                    293,
                    8);
            field_19 = (_DWORD *)this->field_19;
            if ( field_19 )
                *field_19 = MemoryWithInitialization;
            else
                this->field_18 = (int)MemoryWithInitialization;
            this->field_19 = (int)MemoryWithInitialization;
            *MemoryWithInitialization = 0;
            field_20 = 4;
            this->field_20 = 4;
        }
        v6 = this->field_19 + field_20;
        this->field_20 = field_20 + v8;
        ++this->field_21;
        sub_1A500(v6, (int)a2, 0x7FFFFFFF);
        return (char *)v6;
    }
protected:
    void *field_18;
    int field_19;
    int field_20;
    int field_21;
};


