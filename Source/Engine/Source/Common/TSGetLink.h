#pragma once


#include <cstdint>
#include "TSLink.h"
#include "TSLinkedNode.h"
#include "offset_of.h"

template<class T>
class TSGetLink {
public:
    // Static functions
    static TSLink<T> *Link(const TSLinkedNode<T> *nodeptr, ptrdiff_t linkoffset);
};

template<class T>
TSLink<T> *TSGetLink<T>::Link(const TSLinkedNode<T> *nodeptr, ptrdiff_t linkoffset) {
    return reinterpret_cast<TSLink<T> *>(reinterpret_cast<uintptr_t>(nodeptr));
}


