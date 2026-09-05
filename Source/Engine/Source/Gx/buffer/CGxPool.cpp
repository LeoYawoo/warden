#include "CGxPool.h"

// TODO: Reverse engineer from IDA

CGxPool::CGxPool()
    : m_bufList()
    , m_size(0)
    , m_target(GxPoolTarget_Vertex)
    , m_usage(GxPoolUsage_Static) {
}

CGxPool::CGxPool(EGxPoolTarget target, EGxPoolUsage usage, uint32_t size, EGxPoolHintBits /*hint*/, const char * /*name*/)
    : m_bufList()
    , m_size(size)
    , m_target(target)
    , m_usage(usage) {
}

CGxPool::~CGxPool() = default;

EGxPoolUsage CGxPool::GetUsage() const {
    return m_usage;
}

void CGxPool::SetUsage(EGxPoolUsage usage) {
    m_usage = usage;
}
