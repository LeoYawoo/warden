#pragma once

#include "CStringManager.h"
#include "Common/TRefCnt.h"
#include "Common/TSHashObject.h"
#include "Common/Hashkey.h"

class CStringRep : public TRefCnt {
public:
    CStringRep();

    ~CStringRep();

    virtual void sub_2D557C() {
        CStringRep *result = &unk_F6BCE0;
        if (this != &unk_F6BCE0) {
            this->m_refcnt = this->m_refcnt - 1;
            if (!result) {
                CStringManager *v2 = CStringManager::Get();
                v2->Delete(this);
            }
        }
    }

private:
    TSHashObject<CStringRep, HASHKEY_STR> mObj;
    static CStringRep unk_F6BCE0;
};