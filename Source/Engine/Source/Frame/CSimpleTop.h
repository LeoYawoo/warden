#pragma once

#include "CSimpleFrame.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CSimpleTop is a top-level frame

class CSimpleTop : public CSimpleFrame {
public:
    CSimpleTop();
    virtual ~CSimpleTop();

    // Top frame operations
    void SetFocus(CSimpleFrame* frame);
    CSimpleTop* GetTopFrame() const;

protected:
    CSimpleFrame* m_focusedFrame;
};
