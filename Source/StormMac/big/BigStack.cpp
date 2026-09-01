#include "BigStack.h"

// Reverse engineered from Warcraft III binary

BigBuffer &BigStack::Alloc(uint32_t *count) {
    if (m_used < SIZE) {
        *count = 0;
        return m_buffer[m_used++];
    }
    // Fallback: return first buffer
    *count = 0;
    return m_buffer[0];
}

void BigStack::Free(uint32_t count) {
    (void)count;
    if (m_used > 0) {
        m_used--;
    }
}

BigBuffer &BigStack::MakeDistinct(BigBuffer &orig, int32_t required) {
    (void)required;
    // For simplicity, return the original
    return orig;
}

void BigStack::UnmakeDistinct(BigBuffer &orig, BigBuffer &distinct) {
    (void)orig;
    (void)distinct;
    // No-op for simplicity
}
