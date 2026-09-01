#include "CAbilityBaseSell.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7916496

CAbilityBaseSell::CAbilityBaseSell()
    : CAbilityInterfaced(),
      m_stockCount(0),
      m_stockRegenTime(0.0f) {
    // Initialize stock flags
    for (int i = 0; i < 32; i++) {
        m_stockFlags[i] = 0;
    }
    // Virtual table set in constructor
}

CAbilityBaseSell::~CAbilityBaseSell() {
    // Virtual destructor
}

void CAbilityBaseSell::SetStockFlag(int index, int flag) {
    if (index >= 0 && index < 32) {
        m_stockFlags[index] |= flag;
    }
}

bool CAbilityBaseSell::TestStockFlag(int index, int flag) const {
    if (index >= 0 && index < 32) {
        return (m_stockFlags[index] & flag) != 0;
    }
    return false;
}

void CAbilityBaseSell::ClearStockFlag(int index, int flag) {
    if (index >= 0 && index < 32) {
        m_stockFlags[index] &= ~flag;
    }
}

int CAbilityBaseSell::GetStockCount() const {
    return m_stockCount;
}

void CAbilityBaseSell::SetStockCount(int count) {
    m_stockCount = count;
}

float CAbilityBaseSell::GetStockRegenTime() const {
    return m_stockRegenTime;
}

void CAbilityBaseSell::SetStockRegenTime(float time) {
    m_stockRegenTime = time;
}
