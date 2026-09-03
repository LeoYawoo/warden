#include "CDialogEventReg.h"

// Reverse engineered from Warcraft III binary

CDialogEventReg::CDialogEventReg() {}
CDialogEventReg::~CDialogEventReg() {}

void CDialogEventReg::RegisterDialog(int32_t dialogId, int32_t eventId) {
    m_registrations.push_back({dialogId, eventId});
}

void CDialogEventReg::UnregisterDialog(int32_t dialogId) {
    m_registrations.erase(
        std::remove_if(m_registrations.begin(), m_registrations.end(),
            [dialogId](const DialogEvent& de) { return de.dialogId == dialogId; }),
        m_registrations.end());
}

int32_t CDialogEventReg::GetEventId(int32_t dialogId) const {
    for (const auto& reg : m_registrations) {
        if (reg.dialogId == dialogId) {
            return reg.eventId;
        }
    }
    return -1;
}

bool CDialogEventReg::IsRegistered(int32_t dialogId) const {
    for (const auto& reg : m_registrations) {
        if (reg.dialogId == dialogId) {
            return true;
        }
    }
    return false;
}
