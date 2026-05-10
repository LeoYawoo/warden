#pragma once

#include <cstdint>
#include "NTempest/C3Vector.h"
#include "NTempest/CImVector.h"
#include "NTempest/C2Vector.h"

using namespace NTempest;

// Terrain vertex structure (28 bytes in original War3)
// Based on IDA offset analysis: sub_3D14A2, CTerrain::GetVertexPtr, sub_3D5BE0
struct TerrainVertex {
    uint32_t flags;         // +0: height encoded in upper bits, water flags
    uint32_t cellIndex;     // +4: cell index (lower 18 bits valid, mask 0x3FFFF)
    uint8_t textureLayer;   // +8: ground texture layer index
    uint8_t cliffLevel;     // +9: cliff/height level
    uint8_t flags2;         // +10: additional flags
    uint8_t waterEdge;      // +11: water edge flags
    C3Vector normal;        // +12: vertex normal (3 floats = 12 bytes)
    // Total: 24 bytes + padding = 28 bytes
};

static_assert(sizeof(TerrainVertex) == 24, "TerrainVertex should be 24 bytes, plus 4 padding makes 28");

// Represents a terrain chunk for LOD/culling
// Based on 160-byte structure at CTerrain offset +716
struct TerrainChunk {
    uint32_t flags;         // +0: chunk flags
    uint32_t indexCount;    // +4: number of indices
    uint32_t startIndex;    // +8: first index offset
    uint32_t minIndex;      // +12: min vertex index
    uint32_t maxIndex;      // +16: max vertex index
    float minX, minY, maxX, maxY; // +20..+36: bounding box (Z-up world, so XY is horizontal)
    float minH, maxH;       // +40, +44: height range
    // ... more fields to pad to 148 or 160 bytes
};

class CTerrain {
public:
    CTerrain();
    ~CTerrain();

    // Initialize terrain grid
    // cellsPerRow/cellsPerCol: number of terrain cells in each dimension
    // originX/originY: world-space origin of the terrain grid
    bool Initialize(uint32_t cellsPerRow, uint32_t cellsPerCol,
                    float originX, float originY);

    // Load height data into the terrain
    void SetHeights(const float *heights);
    void SetHeight(uint32_t cellX, uint32_t cellY, float height);

    // Get terrain height at a world position (interpolated)
    float GetHeightAt(float worldX, float worldY) const;

    // Get vertex pointer for a cell coordinate
    const TerrainVertex *GetVertex(uint32_t cellX, uint32_t cellY) const;
    TerrainVertex *GetVertex(uint32_t cellX, uint32_t cellY);

    // Find cell index from world position
    // Returns -1 if position is outside terrain bounds
    int32_t FindCell(float worldX, float worldY) const;

    // Get cell coordinates from cell index
    void GetCellCoords(uint32_t cellIndex, uint32_t &cellX, uint32_t &cellY) const;

    // Render the terrain
    void Render();

    // Accessors
    uint32_t GetCellsPerRow() const { return m_cellsPerRow; }
    uint32_t GetCellsPerCol() const { return m_cellsPerCol; }
    uint32_t GetVertexCount() const { return m_vertexCount; }
    float GetOriginX() const { return m_originX; }
    float GetOriginY() const { return m_originY; }
    float GetCellSize() const { return CELL_SIZE; }

    bool IsValid() const { return m_vertices != nullptr && m_initialized; }

    static constexpr float CELL_SIZE = 128.0f;

private:
    void GenerateRenderData();
    void CreateBuffers();
    void UpdateNormals();

    // Grid layout
    uint32_t m_cellsPerRow = 0;     // +45 in IDA (offset 180)
    uint32_t m_cellsPerCol = 0;     // +46 in IDA (offset 184)
    uint32_t m_vertexCount = 0;     // +56 in IDA (offset 224)

    // World-space origin (offset 196, 200 in IDA)
    float m_originX = 0.0f;         // +49
    float m_originY = 0.0f;         // +50

    // Vertex grid: (cellsPerRow+1) × (cellsPerCol+1)
    // Array of TerrainVertex, size = vertexCount * 28
    TerrainVertex *m_vertices = nullptr; // +57 in IDA (offset 228)

    // Vertex colors (used for rendering)
    CImVector *m_vertexColors = nullptr;

    // OpenGL buffers
    uint32_t m_vao = 0;
    uint32_t m_vbo = 0;
    uint32_t m_ibo = 0;
    uint32_t m_indexCount = 0;
    uint32_t m_glslProgram = 0;
    int32_t m_uniformMVP = -1;
    int32_t m_uniformTex0 = -1;

    bool m_initialized = false;
    bool m_buffersValid = false;
};
