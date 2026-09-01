#pragma once

#include "CAgent.h"

// Forward declarations
class CDataStore;

// Reverse engineered from Warcraft III binary
// Address: 0x787784
// CAbility is the base class for all abilities

class CAbility {
public:
    CAbility();
    virtual ~CAbility();

    // Ability operations
    virtual void Activate();
    virtual void Deactivate();
    virtual bool IsActive() const;

    // Get ability level
    int GetLevel() const;

    // Set ability level
    void SetLevel(int level);

    // Get cooldown
    float GetCooldown() const;

    // Set cooldown
    void SetCooldown(float cooldown);

    // Check if on cooldown
    bool IsOnCooldown() const;

    // Update cooldown
    void UpdateCooldown(float deltaTime);

protected:
    // Ability data
    int m_abilityId;      // offset +4
    int m_abilityType;    // offset +8
    int m_level;          // offset +12
    int m_maxLevel;       // offset +16
    float m_cooldown;     // offset +20
    float m_cooldownLeft; // offset +24
    bool m_active;        // offset +28
    int m_flags;          // offset +32
    int m_ownerId;        // offset +36

    // Agent timer (offset +40)
    CAgentTimer m_timer;
};
