#pragma once

#include "CAbilityInterfaced.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7916496
// CAbilityBaseSell is the base sell ability

class CAbilityBaseSell : public CAbilityInterfaced {
public:
    CAbilityBaseSell();
    virtual ~CAbilityBaseSell();

    // Stock operations
    void SetStockFlag(int index, int flag);
    bool TestStockFlag(int index, int flag) const;
    void ClearStockFlag(int index, int flag);

    // Get stock count
    int GetStockCount() const;

    // Set stock count
    void SetStockCount(int count);

    // Get stock regeneration time
    float GetStockRegenTime() const;

    // Set stock regeneration time
    void SetStockRegenTime(float time);

protected:
    int m_stockCount;       // Custom field
    float m_stockRegenTime; // Custom field
    int m_stockFlags[32];   // Stock flags array
};
