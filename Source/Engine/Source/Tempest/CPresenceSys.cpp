#include "CPresenceSys.h"

// Reverse engineered from Warcraft III binary

namespace Tempest {

CPresenceSys::CPresenceSys() : m_systemId(0), m_initialized(false) {
}

CPresenceSys::~CPresenceSys() {
    Shutdown();
}

void CPresenceSys::Initialize() {
    m_initialized = true;
}

void CPresenceSys::Shutdown() {
    m_initialized = false;
}

bool CPresenceSys::IsInitialized() const {
    return m_initialized;
}

int CPresenceSys::GetSystemId() const {
    return m_systemId;
}

void CPresenceSys::SetSystemId(int id) {
    m_systemId = id;
}

} // namespace Tempest
