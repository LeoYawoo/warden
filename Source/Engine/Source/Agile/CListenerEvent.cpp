#include "CListenerEvent.h"

// Reverse engineered from Warcraft III binary
// Address: 0x738F53

CListenerEvent::CListenerEvent() : CEvent(0xFFFFFFFF, nullptr), m_listener(nullptr) {
    // Virtual table set in constructor
}

CListenerEvent::~CListenerEvent() {
    // Virtual destructor
}

void* CListenerEvent::GetListener() const {
    return m_listener;
}

void CListenerEvent::SetListener(void* listener) {
    m_listener = listener;
}
