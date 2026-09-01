#pragma once

#include "Common/TRefCnt.h"

// Reverse engineered from Warcraft III binary
// CObserver is a base class for observing agent changes
class CObserver : public TRefCnt {
public:
    CObserver();
    virtual ~CObserver();

    virtual void OnNotify();
};
