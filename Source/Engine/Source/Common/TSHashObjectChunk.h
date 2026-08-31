#pragma once


#include "TSGrowableArray.h"
#include "TSLink.h"

template<class T, class TKey>
class TSHashObjectChunk {
public:
    // Member variables
    TSGrowableArray<T> m_array;
    TSLink <TSHashObjectChunk<T, TKey>> m_link;
};


