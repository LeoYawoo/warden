#pragma once
// Reverse engineered from Warcraft III binary

#include <cstdint>

class CTerrain {
public:
    CTerrain() = default;
    ~CTerrain() = default;

    void Initialize(uint32_t cellsPerRow, uint32_t cellsPerCol, float originX, float originY);
    uint32_t GetCellsPerRow() const;
    uint32_t GetCellsPerCol() const;
    float GetHeight(uint32_t x, uint32_t y) const;
    void SetHeight(uint32_t x, uint32_t y, float height);
    bool InBoundsInt(int32_t x, int32_t y) const;
    uint32_t GetFlags(int32_t x, int32_t y) const;
    void SetFlags(int32_t x, int32_t y, uint32_t flags);

private:
    uint32_t m_cellsPerRow = 0;
    uint32_t m_cellsPerCol = 0;
    float m_originX = 0.0f;
    float m_originY = 0.0f;
    float *m_heights = nullptr;
};
