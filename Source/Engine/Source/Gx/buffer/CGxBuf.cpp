#include "CGxBuf.h"

// TODO: Reverse engineer from IDA

CGxBuf::CGxBuf()
    : m_linktofull()
    , m_itemSize(0)
    , m_itemCount(0)
    , unk1C(0)
    , unk1D(0)
    , unk1E(0)
    , unk1F(0)
    , m_pool(nullptr)
    , m_size(0)
    , m_offset(0)
    , m_locked(false) {
}

CGxBuf::CGxBuf(CGxPool *pool, uint32_t itemSize, uint32_t itemCount, uint32_t /*index*/)
    : m_linktofull()
    , m_itemSize(itemSize)
    , m_itemCount(itemCount)
    , unk1C(0)
    , unk1D(0)
    , unk1E(0)
    , unk1F(0)
    , m_pool(pool)
    , m_size(itemSize * itemCount)
    , m_offset(0)
    , m_locked(false) {
}

CGxBuf::~CGxBuf() = default;

uint32_t CGxBuf::GetSize() const {
    return m_size;
}

void CGxBuf::SetSize(uint32_t size) {
    m_size = size;
}

uint32_t CGxBuf::GetOffset() const {
    return m_offset;
}

void CGxBuf::SetOffset(uint32_t offset) {
    m_offset = offset;
}

bool CGxBuf::IsLocked() const {
    return m_locked;
}

void CGxBuf::SetLocked(bool locked) {
    m_locked = locked;
}
