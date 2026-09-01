#pragma once

#include <cstdint>
#include "Engine/Source/Agile/CEvent.h"

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// Address: 0x86D7F6
// CTerrainClickEvent is triggered when terrain is clicked

class CTerrainClickEvent : public CEvent {
public:
    CTerrainClickEvent(unsigned int eventType);
    virtual ~CTerrainClickEvent();

    // Get click position
    float GetClickX() const;
    float GetClickY() const;

    // Set click position
    void SetClickPosition(float x, float y);

    // Get terrain
    CTerrain* GetTerrain() const;

    // Set terrain
    void SetTerrain(CTerrain* terrain);

protected:
    float m_clickX;      // offset +20
    float m_clickY;      // offset +24
    CTerrain* m_terrain; // offset +28
    int32_t m_tileX;     // offset +32
    int32_t m_tileY;     // offset +36
};
