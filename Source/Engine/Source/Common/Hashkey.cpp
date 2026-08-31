#include "Hashkey.h"
#include "StormMac/Memory.h"
#include "StormMac/String.h"

bool HASHKEY_NONE::operator==(const HASHKEY_NONE &key) {
    return true;
}

bool HASHKEY_PTR::operator==(const HASHKEY_PTR &key) {
    return this->m_key == key.m_key;
}

HASHKEY_STR::~HASHKEY_STR() {
    if (this->m_str) {
        SMemFree(this->m_str, __FILE__, __LINE__, 0x0);
    }
}

HASHKEY_STR &HASHKEY_STR::operator=(const char *str) {
    if (this->m_str != str) {
        if (this->m_str) {
            SMemFree(this->m_str, __FILE__, __LINE__, 0x0);
        }

        this->m_str = SStrDupA(str, __FILE__, __LINE__);
    }

    return *this;
}

bool HASHKEY_STR::operator==(const char *str) {
    if (this->m_str == str) {
        return true;
    }
    if (!this->m_str || !str) {
        return false;
    }
    return SStrCmp(this->m_str, str, STORM_MAX_STR) == 0;
}

HASHKEY_STRI &HASHKEY_STRI::operator=(const char *str) {
    static_cast<HASHKEY_STR &>(*this) = str;
    return *this;
}

bool HASHKEY_STRI::operator==(const char *str) {
    return SStrCmpI(this->m_str, str, STORM_MAX_STR) == 0;
}

HASHKEY_STRI_P::HASHKEY_STRI_P() {
    this->m_key = 0;
}

bool HASHKEY_STRI_P::operator==(const HASHKEY_STRI_P &key) {
    return this->m_key == key.m_key;
}

HASHKEY_STRIPACKED::HASHKEY_STRIPACKED() {}

HASHKEY_STRIPACKED::HASHKEY_STRIPACKED(const char *key) {
    int newLen;
    int destsize;
    char *dest;
    int v5;
    const char *v6;
    char source[256];
    char v8[256];
    const char *v9[7];

    this->m_str = 0;
    if (key && *key) {
        v8[0] = 0;
        newLen = SStrLen(key);
        v9[0] = key;
        v6 = &key[newLen];
        if (key < &key[newLen]) {
            destsize = 256;
            dest = v8;
            SStrTokenize(v9, source, 0x100u, " ", 0);
            while (source[0]) {
                v5 = SStrCopy(dest, source, destsize);
                dest += v5;
                destsize -= v5;
                if (v9[0] >= v6)
                    break;
                SStrTokenize(v9, source, 0x100u, " ", 0);
            }
        }
        this->m_str = SStrDupA(v8, __FILE__, __LINE__);
    } else {
        this->m_str = 0;
    }
}