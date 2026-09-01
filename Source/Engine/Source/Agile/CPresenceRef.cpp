#include "CPresenceRef.h"

// Reverse engineered from Warcraft III binary
// Address: 0x738698

CPresenceRef::CPresenceRef() : m_field1(0), m_field2(-1), m_field3(-1) {
    // Virtual table set in constructor
}

CPresenceRef::CPresenceRef(const CPresenceRef& other) {
    // Copy constructor implementation
    m_field1 = other.m_field1;
    m_field2 = other.m_field2;
    m_field3 = other.m_field3;
}

CPresenceRef::~CPresenceRef() {
    // Virtual destructor
}

CPresenceRef& CPresenceRef::operator=(CPresenceRef* presence) {
    if (this != presence) {
        m_field1 = presence->m_field1;
        m_field2 = presence->m_field2;
        m_field3 = presence->m_field3;
    }
    return *this;
}

void CPresenceRef::SetPresence(size_t a1, size_t a2) {
    m_field1 = static_cast<int>(a1);
    m_field2 = static_cast<int>(a2);
}
