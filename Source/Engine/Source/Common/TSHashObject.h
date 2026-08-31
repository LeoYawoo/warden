#pragma once

#include <cstdint>
#include "TSLink.h"

template<class T, class TKey>
class TSHashObject {
public:
    // Member variables
    uint32_t m_hashval;
    TSLink<T> m_linktoslot;
    TSLink<T> m_linktofull;
    TKey m_key;
};


