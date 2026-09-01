#pragma once

#include "CAbility.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7897FB
// CAbilityInterfaced is an ability with interface support

class CAbilityInterfaced : public CAbility {
public:
    CAbilityInterfaced();
    virtual ~CAbilityInterfaced();

    // Interface operations
    virtual void OnInterfaceUpdate();
    virtual bool HasInterface() const;

    // Get interface state
    int GetInterfaceState() const;

    // Set interface state
    void SetInterfaceState(int state);

protected:
    int m_interfaceState;  // Custom field
};
