#include "CTerrain.h"

// TODO: Reverse engineer from IDA

void CTerrain::Initialize(uint32_t cellsPerRow, uint32_t cellsPerCol, float originX, float originY) {
    m_cellsPerRow = cellsPerRow;
    m_cellsPerCol = cellsPerCol;
    m_originX = originX;
    m_originY = originY;
    m_valid = true;
}

void CTerrain::SetHeights(float *heights) {
    m_heights = heights;
}

void CTerrain::Render() {
    // TODO: Implement terrain rendering
}
