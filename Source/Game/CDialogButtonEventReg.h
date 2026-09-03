#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CDialogButtonEventReg manages dialog button event registration

class CDialogButtonEventReg {
public:
    CDialogButtonEventReg();
    ~CDialogButtonEventReg();

    // Registration operations
    void RegisterButton(int32_t buttonId, int32_t eventId);
    void UnregisterButton(int32_t buttonId);

    // Query operations
    int32_t GetEventId(int32_t buttonId) const;
    bool IsRegistered(int32_t buttonId) const;

protected:
    struct ButtonEvent {
        int32_t buttonId;
        int32_t eventId;
    };

    std::vector<ButtonEvent> m_registrations;
};
