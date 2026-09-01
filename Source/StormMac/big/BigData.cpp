#include "BigData.h"

// Reverse engineered from Warcraft III binary

TSGrowableArray<uint8_t> &BigData::Output() const {
    return const_cast<TSGrowableArray<uint8_t>&>(m_output);
}

BigBuffer &BigData::Primary() {
    return m_primary;
}

BigStack &BigData::Stack() const {
    return const_cast<BigStack&>(m_stack);
}
