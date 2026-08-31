#pragma once

#include "event/Types.h"
#include "Common/TSLink.h"


class EvtKeyDown {
public:
    // Member variables
    TSLink <EvtKeyDown> link;
    KEY key;
};


