#pragma once


#include <cstdint>

class CHandleObject {
public:
    // Member variables
    int32_t m_refcount = 0;

    // Virtual member functions
    virtual ~CHandleObject() = default;
};

