#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CWorldObjectsClippable manages clippable world objects

class CWorldObjectsClippable {
public:
    CWorldObjectsClippable();
    ~CWorldObjectsClippable();

    // Clippable properties
    int32_t GetObjectId() const;
    void SetObjectId(int32_t id);

    // Clippable state
    bool IsClipped() const;
    void SetClipped(bool clipped);

    bool IsVisible() const;
    void SetVisible(bool visible);

    // Clipping bounds
    float GetClipRadius() const;
    void SetClipRadius(float radius);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_objectId;
    bool m_clipped;
    bool m_visible;
    float m_clipRadius;
    CTerrain* m_terrain;
};
