#pragma once

#include "TSLink.h"
#include <cstdint>
#include "offset_of.h"

template<class T>
class TSGetExplicitLink {
public:
    // Static functions
    static TSLink<T> *Link(const void *nodeptr, ptrdiff_t linkoffset);
};

template<class T>
TSLink<T> *TSGetExplicitLink<T>::Link(const void *nodeptr, ptrdiff_t linkoffset) {
    return reinterpret_cast<TSLink<T> *>((reinterpret_cast<uintptr_t>(nodeptr) + linkoffset));
}


