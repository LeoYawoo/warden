#pragma once

#include <cstdint>
#include <vector>

// Reverse engineered from Warcraft III binary
// CDialogEventReg manages dialog event registration

class CDialogEventReg {
public:
    CDialogEventReg();
    ~CDialogEventReg();

    // Registration operations
    void RegisterDialog(int32_t dialogId, int32_t eventId);
    void UnregisterDialog(int32_t dialogId);

    // Query operations
    int32_t GetEventId(int32_t dialogId) const;
    bool IsRegistered(int32_t dialogId) const;

protected:
    struct DialogEvent {
        int32_t dialogId;
        int32_t eventId;
    };

    std::vector<DialogEvent> m_registrations;
};
