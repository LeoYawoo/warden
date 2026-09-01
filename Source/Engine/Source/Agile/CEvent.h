#pragma once

// Reverse engineered from Warcraft III binary
// Address: 0x74EDDC
// CEvent is the base class for all events

class CEvent {
public:
    CEvent(unsigned int eventType = 0xFFFFFFFF, void* data = nullptr);
    CEvent(const CEvent& other);
    virtual ~CEvent();

    // Get event type
    unsigned int GetEventType() const;

    // Get event data
    void* GetEventData() const;

    // Set event data
    void SetEventData(void* data);

    // Check if event is valid
    bool IsValid() const;

protected:
    // Virtual table pointer
    unsigned int m_eventType;  // offset +8
    void* m_data;              // offset +12
};
