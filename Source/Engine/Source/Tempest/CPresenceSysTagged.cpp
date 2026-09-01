#include "CPresenceSysTagged.h"

// Reverse engineered from Warcraft III binary

namespace Tempest {

CPresenceSysTagged::CPresenceSysTagged() : CPresenceSys(), m_tag(-1) {
}

CPresenceSysTagged::~CPresenceSysTagged() {
}

int CPresenceSysTagged::GetTag() const {
    return m_tag;
}

void CPresenceSysTagged::SetTag(int tag) {
    m_tag = tag;
}

bool CPresenceSysTagged::IsTagged() const {
    return m_tag >= 0;
}

} // namespace Tempest
