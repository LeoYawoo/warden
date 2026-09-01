#pragma once

#include "Position.h"

// Reverse engineered from Warcraft III binary
// Address: 0x77BF67
// SmartPosition extends Position with pathfinding awareness

class SmartPosition : public Position {
public:
    SmartPosition();
    virtual ~SmartPosition();

    // Check if position is valid for pathfinding
    bool IsValid() const;

    // Get region index for pathfinding
    int GetRegionIndex() const;

    // Set region index
    void SetRegionIndex(int index);

private:
    int m_regionIndex;  // Custom field for pathfinding
};
