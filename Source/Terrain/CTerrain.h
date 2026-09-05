#pragma once
// TODO: Stub - reverse engineer from IDA

#include <cstdint>

class CTerrain {
public:
    CTerrain();
    ~CTerrain() = default;

    void Initialize(uint32_t cellsPerRow, uint32_t cellsPerCol, float originX, float originY);
    void SetHeights(float *heights);

    uint32_t GetCellsPerRow() const { return m_cellsPerRow; }
    uint32_t GetCellsPerCol() const { return m_cellsPerCol; }
    float GetCellSize() const { return m_cellSize; }
    float GetOriginX() const { return m_originX; }
    float GetOriginY() const { return m_originY; }
    bool IsValid() const { return m_valid; }
    void Render();

private:
    uint32_t m_cellsPerRow = 0;
    uint32_t m_cellsPerCol = 0;
    float m_originX = 0.0f;
    float m_originY = 0.0f;
    float m_cellSize = 128.0f;
    float *m_heights = nullptr;
    bool m_valid = false;
};
