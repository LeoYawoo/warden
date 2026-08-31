#include "storm/thread/SEvent.h"

SEvent::SEvent(int32_t manualReset, int32_t initialValue)
        : SSyncObject() {
    this->m_opaqueData = CreateEventA(nullptr, manualReset, initialValue, nullptr);
}

int32_t SEvent::Reset() {
    return ResetEvent(this->m_opaqueData);
}

int32_t SEvent::Set() {
    return SetEvent(this->m_opaqueData);
}
