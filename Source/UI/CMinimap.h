#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CMinimap displays the minimap

class CMinimap {
public:
    CMinimap();
    ~CMinimap();

    // Minimap properties
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    void SetSize(int32_t width, int32_t height);

    // Minimap state
    bool IsVisible() const;
    void SetVisible(bool visible);

    // Minimap terrain
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_width;
    int32_t m_height;
    bool m_visible;
    CTerrain* m_terrain;
};
