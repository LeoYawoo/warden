#pragma once

#include <cstdint>
#include "Graphic/gll/GLBuffer.h"
#include "Graphic/gll/GLVertexFormat.h"
#include "Graphic/gll/GLTypes.h"

class GLDevice;

class TerrainRenderer {
public:
    TerrainRenderer();
    ~TerrainRenderer();

    bool Initialize(uint32_t gridSize, float spacing, float heightScale);

    void Render();

    void Destroy();

    bool IsValid() const { return m_vbo != nullptr; }

private:
    void GenerateHeightmap();
    bool CreateBuffers();
    bool CompileShaders();

#pragma pack(push, 1)
    struct TerrainVertex {
        float px, py, pz;       // slot 0: position
        float nx, ny, nz;       // slot 1: normal
        uint8_t r, g, b, a;     // slot 2: color
    };
#pragma pack(pop)

    uint32_t m_gridSize = 33;
    float m_spacing = 8.0f;
    float m_heightScale = 50.0f;

    uint32_t m_vertexCount = 0;
    uint32_t m_indexCount = 0;

    float *m_heightmap = nullptr;

    GLBuffer *m_vbo = nullptr;
    GLBuffer *m_ibo = nullptr;
    GLVertexFormat m_vertexFormat;

    // GLSL shader for core profile
    uint32_t m_glslProgram = 0;
    uint32_t m_vao = 0;
    int32_t m_uniformMVP = -1;
};
