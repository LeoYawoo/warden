#include "storm/thread/SSemaphore.h"

SSemaphore::SSemaphore(uint32_t initialCount, uint32_t maximumCount)
        : SSyncObject() {
    this->m_opaqueData = CreateSemaphoreA(nullptr, initialCount, maximumCount, nullptr);
}

int32_t SSemaphore::Signal(uint32_t count) {
    return ReleaseSemaphore(this->m_opaqueData, count, nullptr);
}
