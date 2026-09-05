#pragma once

#include "Event/CEvent.h"

// Reverse engineered from Warcraft III binary
// Address: 0x738F53
// CListenerEvent is an event for listener notifications

class CListenerEvent : public CEvent {
public:
    CListenerEvent();
    virtual ~CListenerEvent();

    // Get listener
    void* GetListener() const;

    // Set listener
    void SetListener(void* listener);

protected:
    void* m_listener;  // Custom field
};
