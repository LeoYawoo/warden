#include "storm/thread/CSRWLock.h"

void CSRWLock::Enter(int32_t forwriting) {
    SRWLock::SURWLockEnter(&this->m_opaqueData, forwriting);
}

void CSRWLock::Leave(int32_t fromwriting) {
    SRWLock::SURWLockLeave(&this->m_opaqueData, fromwriting);
}
