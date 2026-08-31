#pragma once

#include <cstdint>

class SFile;

class Cfg_ConfigsRec {
public:
    int32_t m_ID;
    int32_t m_realmType;
    int32_t m_playerKillingAllowed;
    int32_t m_roleplaying;

    static const char *GetFilename();

    static uint32_t GetNumColumns();

    static uint32_t GetRowSize();

    int32_t GetID();

    bool Read(SFile *f, const char *stringBuffer);
};


