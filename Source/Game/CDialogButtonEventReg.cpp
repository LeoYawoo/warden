#include "CDialogButtonEventReg.h"

// Reverse engineered from Warcraft III binary

CDialogButtonEventReg::CDialogButtonEventReg() {}
CDialogButtonEventReg::~CDialogButtonEventReg() {}

void CDialogButtonEventReg::RegisterButton(int32_t buttonId, int32_t eventId) {
    m_registrations.push_back({buttonId, eventId});
}

void CDialogButtonEventReg::UnregisterButton(int32_t buttonId) {
    m_registrations.erase(
        std::remove_if(m_registrations.begin(), m_registrations.end(),
            [buttonId](const ButtonEvent& be) { return be.buttonId == buttonId; }),
        m_registrations.end());
}

int32_t CDialogButtonEventReg::GetEventId(int32_t buttonId) const {
    for (const auto& reg : m_registrations) {
        if (reg.buttonId == buttonId) {
            return reg.eventId;
        }
    }
    return -1;
}

bool CDialogButtonEventReg::IsRegistered(int32_t buttonId) const {
    for (const auto& reg : m_registrations) {
        if (reg.buttonId == buttonId) {
            return true;
        }
    }
    return false;
}
