#include "CItem.h"

// Reverse engineered from Warcraft III binary
// Address: 0x97B3CC

CItem::CItem()
    : CAgentBaseAbs(),
      m_cooldown(0.0f),
      m_position(),
      m_itemId(0),
      m_itemType(-1),
      m_charges(1),
      m_flags(0),
      m_ownerId(0),
      m_disposed(0),
      m_ownerRef(),
      m_lastHolder(0),
      m_useTimer(),
      m_cooldownTimer() {
    // Initialize refs
    for (int i = 0; i < 4; i++) {
        // AgentRefMini default construction
    }
    // Virtual table set in constructor
}

CItem::~CItem() {
    // Virtual destructor
}

int32_t CItem::GetItemId() const {
    return m_itemId;
}

void CItem::SetItemId(int32_t id) {
    m_itemId = id;
}

int32_t CItem::GetItemType() const {
    return m_itemType;
}

void CItem::SetItemType(int32_t type) {
    m_itemType = type;
}

int32_t CItem::GetCharges() const {
    return m_charges;
}

void CItem::SetCharges(int32_t charges) {
    m_charges = charges;
}

bool CItem::IsPermanent() const {
    return (m_flags & 0x01) != 0;
}

void CItem::SetPermanent(bool permanent) {
    if (permanent) {
        m_flags |= 0x01;
    } else {
        m_flags &= ~0x01;
    }
}

bool CItem::IsOwned() const {
    return m_ownerId != 0;
}

void CItem::SetOwned(bool owned) {
    if (owned) {
        m_flags |= 0x02;
    } else {
        m_flags &= ~0x02;
    }
}

bool CItem::IsDisposed() const {
    return m_disposed != 0;
}

void CItem::SetDisposed(bool disposed) {
    m_disposed = disposed ? 1 : 0;
}

const Position& CItem::GetPosition() const {
    return m_position;
}

void CItem::SetPosition(const Position& pos) {
    m_position = pos;
}

CUnit* CItem::GetOwner() const {
    return reinterpret_cast<CUnit*>(m_ownerRef.GetAgent());
}

void CItem::SetOwner(CUnit* owner) {
    m_ownerRef = reinterpret_cast<CAgent*>(owner);
}
