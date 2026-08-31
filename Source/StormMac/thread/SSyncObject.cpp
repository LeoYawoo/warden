#include "storm/thread/SSyncObject.h"


SSyncObject::SSyncObject() {
#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    pthread_mutex_init(&this->m_mutex, 0);
#endif
}

SSyncObject::~SSyncObject() {
    this->Close();
}

void SSyncObject::Close() {
    if (this->m_opaqueData) {
        CloseHandle(this->m_opaqueData);
        this->m_opaqueData = nullptr;
    }
}

bool SSyncObject::Valid() {
    return this->m_opaqueData != nullptr;
}

uint32_t SSyncObject::Wait(uint32_t timeoutMs) {
    return WaitForSingleObject(this->m_opaqueData, timeoutMs);
}
