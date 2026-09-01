#pragma once

#include "Common/TRefCnt.h"

// Reverse engineered from Warcraft III binary
// CPresenceRef is the base class for agent fields and relations
class CPresenceRef : public TRefCnt {
public:
    CPresenceRef();
    CPresenceRef(const CPresenceRef& other);
    virtual ~CPresenceRef();

    CPresenceRef& operator=(CPresenceRef* presence);

    void SetPresence(size_t a1, size_t a2);

protected:
    int m_field1;  // offset +4
    int m_field2;  // offset +8
    int m_field3;  // offset +12
};
