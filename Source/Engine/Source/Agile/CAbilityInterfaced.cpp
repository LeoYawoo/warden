#include "CAbilityInterfaced.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7897FB

CAbilityInterfaced::CAbilityInterfaced() : CAbility(), m_interfaceState(0) {
    // Virtual table set in constructor
}

CAbilityInterfaced::~CAbilityInterfaced() {
    // Virtual destructor
}

void CAbilityInterfaced::OnInterfaceUpdate() {
    // Default implementation does nothing
}

bool CAbilityInterfaced::HasInterface() const {
    return m_interfaceState != 0;
}

int CAbilityInterfaced::GetInterfaceState() const {
    return m_interfaceState;
}

void CAbilityInterfaced::SetInterfaceState(int state) {
    m_interfaceState = state;
}
