#pragma once

#include <cstdint>
#include <vector>

// Reverse engineered from Warcraft III binary
// CPathingFootprint manages pathfinding footprints

class CPathingFootprint {
public:
    CPathingFootprint();
    ~CPathingFootprint();

    // Footprint operations
    bool Initialize(int32_t width, int32_t height);
    void Shutdown();
    bool IsInitialized() const;

    // Footprint state
    void SetFootprint(int32_t x, int32_t y, bool walkable);
    bool IsWalkable(int32_t x, int32_t y) const;

    // Footprint properties
    int32_t GetWidth() const;
    int32_t GetHeight() const;

protected:
    bool m_initialized;
    int32_t m_width;
    int32_t m_height;
    std::vector<bool> m_footprintData;
};
