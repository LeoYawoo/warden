#include "BigBuffer.h"
#include "StormMac/Memory.h"

// Reverse engineered from Warcraft III binary

uint32_t &BigBuffer::operator[](uint32_t index) {
    GrowToFit(index);
    return m_data[index];
}

uint32_t BigBuffer::operator[](uint32_t index) const {
    if (index < m_data.Count()) {
        return const_cast<TSGrowableArray<uint32_t>&>(m_data)[index];
    }
    return 0;
}

void BigBuffer::Clear() {
    m_data.Clear();
    m_offset = 0;
}

uint32_t BigBuffer::Count() const {
    return m_data.Count();
}

void BigBuffer::GrowToFit(uint32_t index) {
    if (index >= m_data.Count()) {
        m_data.SetCount(index + 1);
    }
}

int32_t BigBuffer::IsUsed(uint32_t index) const {
    return index < m_data.Count() && const_cast<TSGrowableArray<uint32_t>&>(m_data)[index] != 0;
}

void BigBuffer::SetCount(uint32_t count) {
    m_data.SetCount(count);
}

void BigBuffer::SetOffset(uint32_t offset) {
    m_offset = offset;
}

void BigBuffer::Trim() const {
    // Trim unused elements
}
