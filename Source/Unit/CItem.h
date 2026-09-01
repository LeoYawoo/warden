#pragma once

#include "Engine/Source/Agile/CAgent.h"
#include "Engine/Source/Agile/AgentRefMini.h"
#include "Engine/Source/Agile/Position.h"
#include "Engine/Source/Agile/Float.h"

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// Address: 0x97B3CC
// CItem represents an item in the game

class CItem : public CAgentBaseAbs {
public:
    CItem();
    virtual ~CItem();

    // Item properties
    int32_t GetItemId() const;
    void SetItemId(int32_t id);

    int32_t GetItemType() const;
    void SetItemType(int32_t type);

    int32_t GetCharges() const;
    void SetCharges(int32_t charges);

    bool IsPermanent() const;
    void SetPermanent(bool permanent);

    // Item state
    bool IsOwned() const;
    void SetOwned(bool owned);

    bool IsDisposed() const;
    void SetDisposed(bool disposed);

    // Item position
    const Position& GetPosition() const;
    void SetPosition(const Position& pos);

    // Item owner
    CUnit* GetOwner() const;
    void SetOwner(CUnit* owner);

protected:
    // Item data (offset +84 to +240)
    Float m_cooldown;           // offset +84
    Position m_position;        // offset +100
    int32_t m_itemId;           // offset +116
    int32_t m_itemType;         // offset +120
    int32_t m_charges;          // offset +124
    int32_t m_flags;            // offset +128
    int32_t m_ownerId;          // offset +132
    int32_t m_disposed;         // offset +136

    AgentRefMini m_ownerRef;    // offset +140

    // Additional agent references
    AgentRefMini m_refs[4];     // offset +156 to +204

    int32_t m_lastHolder;       // offset +204

    // Timers
    CAgentTimer m_useTimer;     // offset +208
    CAgentTimer m_cooldownTimer;// offset +228
};
