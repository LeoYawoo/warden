#pragma once

#include "TSHashTable.h"

template<typename T, typename N, int>
class TAllocatorHashTable : public TSHashTable<T, N> {
public:
    TAllocatorHashTable() {}

    ~TAllocatorHashTable() {}
};