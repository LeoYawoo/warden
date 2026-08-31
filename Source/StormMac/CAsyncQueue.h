#pragma once

#include "CAsyncObject.h"
#include "Common/TSLinkedNode.h"
#include "Common/TSExplicitList.h"
#include <cstdint>


class CAsyncQueue : public TSLinkedNode<CAsyncQueue> {
public:
    // Member variables
    STORM_EXPLICIT_LIST(CAsyncObject, link) readList;
    STORM_EXPLICIT_LIST(CAsyncObject, link) list14;
    int32_t int20;
};


