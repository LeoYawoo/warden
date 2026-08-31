#include "CTerrain.h"
#include "Engine/Source/Gx/gll/GLDevice.h"
#include "Engine/Source/Gx/gll/GLBuffer.h"
#include "Engine/Source/Gx/gll/GLVertexFormat.h"
#include "Engine/Source/Gx/Device.h"
#include "Engine/Source/Gx/CCamera.h"
#include "glad/glad.h"
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>

CTerrain::CTerrain() = default;

CTerrain::~CTerrain() {
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_ibo) {
        glDeleteBuffers(1, &m_ibo);
        m_ibo = 0;
    }
    if (m_glslProgram) {
        glDeleteProgram(m_glslProgram);
        m_glslProgram = 0;
    }

    delete[] m_vertices;
    m_vertices = nullptr;
    delete[] m_vertexColors;
    m_vertexColors = nullptr;
    m_initialized = false;
    m_buffersValid = false;
}

bool CTerrain::Initialize(uint32_t cellsPerRow, uint32_t cellsPerCol,
                          float originX, float originY) {
    if (m_initialized) {
        // Clean up existing state
        delete[] m_vertices;
        m_vertices = nullptr;
        if (m_vao) { glDeleteVertexArrays(1, &m_vao); m_vao = 0; }
        if (m_vbo) { glDeleteBuffers(1, &m_vbo); m_vbo = 0; }
        if (m_ibo) { glDeleteBuffers(1, &m_ibo); m_ibo = 0; }
        if (m_glslProgram) { glDeleteProgram(m_glslProgram); m_glslProgram = 0; }
    }

    m_cellsPerRow = cellsPerRow;
    m_cellsPerCol = cellsPerCol;
    m_originX = originX;
    m_originY = originY;

    // Vertex grid is (cells+1) × (cells+1)
    m_vertexCount = (cellsPerRow + 1) * (cellsPerCol + 1);

    // Allocate vertex array
    m_vertices = new TerrainVertex[m_vertexCount];
    memset(m_vertices, 0, m_vertexCount * sizeof(TerrainVertex));

    // Initialize vertex positions (flat grid initially)
    for (uint32_t cy = 0; cy <= cellsPerCol; cy++) {
        for (uint32_t cx = 0; cx <= cellsPerRow; cx++) {
            uint32_t idx = cy * (cellsPerRow + 1) + cx;
            auto &v = m_vertices[idx];
            v.cellIndex = cy * (cellsPerRow + 1) + cx;
            v.textureLayer = 0;
            v.cliffLevel = 0;
            v.flags2 = 0;
            v.waterEdge = 0;
            v.normal = C3Vector(0.0f, 0.0f, 1.0f); // Z-up
        }
    }

    m_initialized = true;
    return true;
}

void CTerrain::SetHeights(const float *heights) {
    if (!m_initialized || !heights) return;

    for (uint32_t i = 0; i < m_vertexCount; i++) {
        // Encode height into flags (original uses upper bits for height)
        float h = heights[i];
        int32_t hInt = static_cast<int32_t>(h * 16.0f); // fixed-point: 1/16 unit precision
        m_vertices[i].flags = (hInt & 0xFFFF) | (m_vertices[i].flags & 0xFFFF0000);
    }

    UpdateNormals();
    m_buffersValid = false;
}

void CTerrain::SetHeight(uint32_t cellX, uint32_t cellY, float height) {
    if (!m_initialized) return;
    if (cellX > m_cellsPerRow || cellY > m_cellsPerCol) return;

    uint32_t idx = cellY * (m_cellsPerRow + 1) + cellX;
    int32_t hInt = static_cast<int32_t>(height * 16.0f);
    m_vertices[idx].flags = (hInt & 0xFFFF) | (m_vertices[idx].flags & 0xFFFF0000);

    UpdateNormals();
    m_buffersValid = false;
}

float CTerrain::GetHeightAt(float worldX, float worldY) const {
    // Convert world position to cell-space
    float fx = (worldX - m_originX) / CELL_SIZE;
    float fy = (worldY - m_originY) / CELL_SIZE;

    int32_t cx = static_cast<int32_t>(fx);
    int32_t cy = static_cast<int32_t>(fy);

    if (cx < 0 || cy < 0 ||
        static_cast<uint32_t>(cx) >= m_cellsPerRow ||
        static_cast<uint32_t>(cy) >= m_cellsPerCol) {
        return 0.0f;
    }

    float lx = fx - static_cast<float>(cx); // local x in cell [0,1]
    float ly = fy - static_cast<float>(cy); // local y in cell [0,1]

    auto GetH = [this](uint32_t x, uint32_t y) -> float {
        uint32_t idx = y * (m_cellsPerRow + 1) + x;
        int32_t hInt = static_cast<int16_t>(m_vertices[idx].flags & 0xFFFF);
        return static_cast<float>(hInt) / 16.0f;
    };

    float h00 = GetH(cx, cy);
    float h10 = GetH(cx + 1, cy);
    float h01 = GetH(cx, cy + 1);
    float h11 = GetH(cx + 1, cy + 1);

    // Bilinear interpolation
    float h0 = h00 + (h10 - h00) * lx;
    float h1 = h01 + (h11 - h01) * lx;
    return h0 + (h1 - h0) * ly;
}

int32_t CTerrain::FindCell(float worldX, float worldY) const {
    // Based on sub_3D14A2 from IDA:
    // cellX = (int16_t)((x - originX) * (1/128.0) + 0.5)
    // cellY = (int16_t)((y - originY) * (1/128.0) + 0.5)
    float fx = (worldX - m_originX) * (1.0f / CELL_SIZE) + 0.5f;
    float fy = (worldY - m_originY) * (1.0f / CELL_SIZE) + 0.5f;

    int32_t cx = static_cast<int32_t>(fx);
    int32_t cy = static_cast<int32_t>(fy);

    if (cx < 0 || cy < 0 ||
        static_cast<uint32_t>(cx) > m_cellsPerRow ||
        static_cast<uint32_t>(cy) > m_cellsPerCol) {
        return -1;
    }

    // Return vertex index in the grid
    return cy * (m_cellsPerRow + 1) + cx;
}

void CTerrain::GetCellCoords(uint32_t cellIndex, uint32_t &cellX, uint32_t &cellY) const {
    // Based on CTerrain::GetVertCoords from IDA:
    // x = cellIndex % (cellsPerRow + 1)
    // y = cellIndex / (cellsPerRow + 1)
    cellX = cellIndex % (m_cellsPerRow + 1);
    cellY = cellIndex / (m_cellsPerRow + 1);
}

const TerrainVertex *CTerrain::GetVertex(uint32_t cellX, uint32_t cellY) const {
    if (!m_vertices || cellX > m_cellsPerRow || cellY > m_cellsPerCol) return nullptr;
    return &m_vertices[cellY * (m_cellsPerRow + 1) + cellX];
}

TerrainVertex *CTerrain::GetVertex(uint32_t cellX, uint32_t cellY) {
    if (!m_vertices || cellX > m_cellsPerRow || cellY > m_cellsPerCol) return nullptr;
    return &m_vertices[cellY * (m_cellsPerRow + 1) + cellX];
}

void CTerrain::UpdateNormals() {
    for (uint32_t cy = 0; cy <= m_cellsPerCol; cy++) {
        for (uint32_t cx = 0; cx <= m_cellsPerRow; cx++) {
            // Compute normal from height differences with neighbors
            auto GetH = [this](int32_t x, int32_t y) -> float {
                if (x < 0 || y < 0 ||
                    static_cast<uint32_t>(x) > m_cellsPerRow ||
                    static_cast<uint32_t>(y) > m_cellsPerCol) {
                    return 0.0f;
                }
                uint32_t idx = static_cast<uint32_t>(y) * (m_cellsPerRow + 1) + static_cast<uint32_t>(x);
                int32_t hInt = static_cast<int16_t>(m_vertices[idx].flags & 0xFFFF);
                return static_cast<float>(hInt) / 16.0f;
            };

            float hL = GetH(static_cast<int32_t>(cx) - 1, static_cast<int32_t>(cy));
            float hR = GetH(static_cast<int32_t>(cx) + 1, static_cast<int32_t>(cy));
            float hD = GetH(static_cast<int32_t>(cx), static_cast<int32_t>(cy) - 1);
            float hU = GetH(static_cast<int32_t>(cx), static_cast<int32_t>(cy) + 1);

            // Cross product of partial derivatives in Z-up system
            // dx = (1, 0, dh/dx), dy = (0, 1, dh/dy)
            float dhdx = (hR - hL) / (2.0f * CELL_SIZE);
            float dhdy = (hU - hD) / (2.0f * CELL_SIZE);

            float nx = -dhdx;
            float ny = -dhdy;
            float nz = 1.0f;
            float len = std::sqrt(nx * nx + ny * ny + nz * nz);
            float invLen = 1.0f / (len + 0.00001f);

            uint32_t idx = cy * (m_cellsPerRow + 1) + cx;
            m_vertices[idx].normal.x = nx * invLen;
            m_vertices[idx].normal.y = ny * invLen;
            m_vertices[idx].normal.z = nz * invLen;
        }
    }
}

void CTerrain::GenerateRenderData() {
    if (!m_initialized) return;

    // Build vertex color array based on height
    delete[] m_vertexColors;
    m_vertexColors = new CImVector[m_vertexCount];

    float minH = 1e10f, maxH = -1e10f;
    for (uint32_t i = 0; i < m_vertexCount; i++) {
        int32_t hInt = static_cast<int16_t>(m_vertices[i].flags & 0xFFFF);
        float h = static_cast<float>(hInt) / 16.0f;
        minH = std::min(minH, h);
        maxH = std::max(maxH, h);
    }

    float invRange = 1.0f / (maxH - minH + 0.001f);

    for (uint32_t i = 0; i < m_vertexCount; i++) {
        int32_t hInt = static_cast<int16_t>(m_vertices[i].flags & 0xFFFF);
        float h = static_cast<float>(hInt) / 16.0f;
        float t = (h - minH) * invRange;

        uint8_t r, g, b;
        if (t < 0.5f) {
            float t2 = t * 2.0f;
            r = static_cast<uint8_t>(t2 * 120.0f);
            g = static_cast<uint8_t>((1.0f - t2 * 0.3f) * 180.0f);
            b = static_cast<uint8_t>((1.0f - t2) * 60.0f);
        } else {
            float t2 = (t - 0.5f) * 2.0f;
            r = static_cast<uint8_t>(120.0f + t2 * 135.0f);
            g = static_cast<uint8_t>(126.0f + t2 * 129.0f);
            b = static_cast<uint8_t>(t2 * 200.0f);
        }
        m_vertexColors[i] = CImVector();
        m_vertexColors[i].value = CImVector::MakeARGB(255, r, g, b);
    }
}

void CTerrain::CreateBuffers() {
    if (!m_initialized) return;

    // Clean up old buffers
    if (m_vao) { glDeleteVertexArrays(1, &m_vao); m_vao = 0; }
    if (m_vbo) { glDeleteBuffers(1, &m_vbo); m_vbo = 0; }
    if (m_ibo) { glDeleteBuffers(1, &m_ibo); m_ibo = 0; }

    GenerateRenderData();

    // Create vertex buffer: position + normal + color + texcoord
    struct RenderVertex {
        float px, py, pz;
        float nx, ny, nz;
        uint8_t r, g, b, a;
        float tx, ty;
    };

    uint32_t gx = m_cellsPerRow + 1;
    uint32_t gy = m_cellsPerCol + 1;

    auto *verts = new RenderVertex[m_vertexCount];
    for (uint32_t cy = 0; cy < gy; cy++) {
        for (uint32_t cz = 0; cz < gx; cz++) {
            uint32_t idx = cy * gx + cz;
            auto &v = m_vertices[idx];
            int32_t hInt = static_cast<int16_t>(v.flags & 0xFFFF);
            float h = static_cast<float>(hInt) / 16.0f;

            // World position: X = col * 128, Y = row * 128, Z = height
            verts[idx].px = m_originX + static_cast<float>(cz) * CELL_SIZE;
            verts[idx].py = m_originY + static_cast<float>(cy) * CELL_SIZE;
            verts[idx].pz = h;

            verts[idx].nx = v.normal.x;
            verts[idx].ny = v.normal.y;
            verts[idx].nz = v.normal.z;

            auto &col = m_vertexColors[idx];
            verts[idx].r = col.r;
            verts[idx].g = col.g;
            verts[idx].b = col.b;
            verts[idx].a = col.a;

            // Texture coordinates
            verts[idx].tx = static_cast<float>(cz) / static_cast<float>(gx - 1);
            verts[idx].ty = static_cast<float>(cy) / static_cast<float>(gy - 1);
        }
    }

    // Create triangle indices
    m_indexCount = m_cellsPerRow * m_cellsPerCol * 6;
    auto *indices = new uint16_t[m_indexCount];
    uint32_t idx = 0;
    for (uint32_t cy = 0; cy < m_cellsPerCol; cy++) {
        for (uint32_t cx = 0; cx < m_cellsPerRow; cx++) {
            uint32_t i0 = cy * gx + cx;
            uint32_t i1 = cy * gx + (cx + 1);
            uint32_t i2 = (cy + 1) * gx + cx;
            uint32_t i3 = (cy + 1) * gx + (cx + 1);

            indices[idx++] = static_cast<uint16_t>(i0);
            indices[idx++] = static_cast<uint16_t>(i1);
            indices[idx++] = static_cast<uint16_t>(i2);

            indices[idx++] = static_cast<uint16_t>(i1);
            indices[idx++] = static_cast<uint16_t>(i3);
            indices[idx++] = static_cast<uint16_t>(i2);
        }
    }

    // Create OpenGL buffers
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(RenderVertex), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(uint16_t), indices, GL_STATIC_DRAW);

    // Vertex attributes: location=0: position, location=1: normal, location=2: color, location=3: texcoord
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RenderVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(RenderVertex), (void*)offsetof(RenderVertex, nx));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(RenderVertex), (void*)offsetof(RenderVertex, r));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(RenderVertex), (void*)offsetof(RenderVertex, tx));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    delete[] verts;
    delete[] indices;

    // Compile shaders for terrain rendering
    const char *vsSrc = R"(#version 330
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aNormal;
        layout(location = 2) in vec4 aColor;
        layout(location = 3) in vec2 aTexCoord;
        uniform mat4 uMVP;
        out vec3 vNormal;
        out vec4 vColor;
        out vec2 vTexCoord;
        void main() {
            gl_Position = uMVP * vec4(aPos, 1.0);
            vNormal = aNormal;
            vColor = aColor;
            vTexCoord = aTexCoord;
        })";

    const char *fsSrc = R"(#version 330
        in vec3 vNormal;
        in vec4 vColor;
        in vec2 vTexCoord;
        out vec4 fragColor;
        uniform sampler2D uTex0;
        void main() {
            vec3 lightDir = normalize(vec3(0.5, 0.5, 1.0));
            vec3 n = normalize(vNormal);
            float diff = max(dot(n, lightDir), 0.0);
            float amb = 0.3;
            vec3 lit = vColor.rgb * (amb + diff * 0.7);
            fragColor = vec4(lit, 1.0);
        })";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, nullptr);
    glCompileShader(fs);

    GLint ok;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
    if (!ok) { char buf[512]; glGetShaderInfoLog(vs, 512, nullptr, buf); fprintf(stderr, "CTerrain VS: %s\n", buf); }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
    if (!ok) { char buf[512]; glGetShaderInfoLog(fs, 512, nullptr, buf); fprintf(stderr, "CTerrain FS: %s\n", buf); }

    m_glslProgram = glCreateProgram();
    glAttachShader(m_glslProgram, vs);
    glAttachShader(m_glslProgram, fs);
    glLinkProgram(m_glslProgram);

    glGetProgramiv(m_glslProgram, GL_LINK_STATUS, &ok);
    if (!ok) { char buf[512]; glGetProgramInfoLog(m_glslProgram, 512, nullptr, buf); fprintf(stderr, "CTerrain Link: %s\n", buf); }

    glDeleteShader(vs);
    glDeleteShader(fs);

    m_uniformMVP = glGetUniformLocation(m_glslProgram, "uMVP");
    m_uniformTex0 = glGetUniformLocation(m_glslProgram, "uTex0");

    m_buffersValid = (ok != 0);
}

void CTerrain::Render() {
    if (!m_initialized || !m_glslProgram) return;

    if (!m_buffersValid) {
        CreateBuffers();
    }

    GLDevice *device = GLDevice::Get();
    if (!device) return;

    // Get view/projection matrices from the device
    float proj[16], view[16], world[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    memcpy(proj, device->m_States.fixedFunc.transforms.projection.m, sizeof(proj));
    memcpy(view, device->m_States.fixedFunc.transforms.view.m, sizeof(view));

    // Y-flip projection for OpenGL
    proj[4] *= -1.0f; proj[5] *= -1.0f; proj[6] *= -1.0f; proj[7] *= -1.0f;

    // Compute MVP = proj * view * world (column-major)
    auto mulMat4 = [](const float *a, const float *b, float *dst) {
        for (int col = 0; col < 4; col++)
            for (int row = 0; row < 4; row++)
                dst[col*4 + row] = a[row]*b[col*4] + a[4+row]*b[col*4+1] + a[8+row]*b[col*4+2] + a[12+row]*b[col*4+3];
    };

    float viewWorld[16], mvp[16];
    mulMat4(view, world, viewWorld);
    mulMat4(proj, viewWorld, mvp);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glDisable(GL_CULL_FACE);

    glUseProgram(m_glslProgram);
    glUniformMatrix4fv(m_uniformMVP, 1, GL_FALSE, mvp);
    glUniform1i(m_uniformTex0, 0);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
    glUseProgram(0);

    // Mark state dirty for CGxDevice
    if (g_theGxDevicePtr) {
        g_theGxDevicePtr->IRsDirty(GxRs_DepthTest);
        g_theGxDevicePtr->IRsDirty(GxRs_DepthFunc);
        g_theGxDevicePtr->IRsDirty(GxRs_DepthWrite);
        g_theGxDevicePtr->IRsDirty(GxRs_Culling);
        g_theGxDevicePtr->IRsDirty(GxRs_VertexShader);
        g_theGxDevicePtr->IRsDirty(GxRs_PixelShader);
    }
}
