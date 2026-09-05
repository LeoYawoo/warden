#pragma once


#include <cstdlib>
#include "TSGetExplicitLink.h"
#include "TSList.h"
#include "offset_of.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

#define STORM_EXPLICIT_LIST(T, link) TSExplicitList<T, offsetof(T, link)>

template<class T, size_t offset>
class TSExplicitList : public TSList<T, TSGetExplicitLink<T>> {
public:
    // Member functions
    TSExplicitList();
};

template<class T, size_t offset>
TSExplicitList<T, offset>::TSExplicitList()
        : TSList<T, TSGetExplicitLink<T>>() {
    this->SetLinkOffset(offset);
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


