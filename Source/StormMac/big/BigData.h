#pragma once


#include "BigBuffer.h"
#include "BigStack.h"

class BigData {
public:
    // Member variables
    BigBuffer m_primary;
    BigStack m_stack;
    TSGrowableArray<uint8_t> m_output;

    // Member functions
    TSGrowableArray<uint8_t> &Output() const;

    BigBuffer &Primary();

    BigStack &Stack() const;
};

