#pragma once

#include <cstdint>

class CSimpleFontedFrameFont;

class CSimpleFontedFrame {
public:
    // Virtual member functions
    virtual void FontUpdated(CSimpleFontedFrameFont *, int32_t) = 0;
};
