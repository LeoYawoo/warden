#include "TerrainRenderer.h"
#include "Graphic/gll/GLDevice.h"
#include "Graphic/gll/GLVertexArray.h"
#include "Graphic/Device.h"
#include "Graphic/Types.h"
#include "glad/glad.h"
#include <cmath>
#include <algorithm>
#include <cstdio>
#include "Common/DebugOut.h"

TerrainRenderer::TerrainRenderer() = default;

TerrainRenderer::~TerrainRenderer() {
    Destroy();
}

bool TerrainRenderer::Initialize(uint32_t gridSize, float spacing, float heightScale) {
    if (IsValid()) Destroy();

    m_gridSize = gridSize;
    m_spacing = spacing;
    m_heightScale = heightScale;

    m_vertexCount = m_gridSize * m_gridSize;
    m_indexCount = (m_gridSize - 1) * (m_gridSize - 1) * 6;

    GenerateHeightmap();
    bool ok = CreateBuffers();

    delete[] m_heightmap;
    m_heightmap = nullptr;

    return ok;
}

void TerrainRenderer::GenerateHeightmap() {
    const uint32_t g = m_gridSize;
    const float scale = m_heightScale;

    m_heightmap = new float[m_vertexCount];

    for (uint32_t z = 0; z < g; ++z) {
        for (uint32_t x = 0; x < g; ++x) {
            float fx = static_cast<float>(x) / static_cast<float>(g - 1);
            float fz = static_cast<float>(z) / static_cast<float>(g - 1);

            float h = 0.0f;
            h += sinf(fx * 4.0f + 1.3f) * cosf(fz * 3.0f + 0.7f) * 0.5f;
            h += sinf(fx * 8.0f - fz * 5.0f + 2.1f) * 0.25f;
            h += cosf(fx * 12.0f + fz * 7.0f) * 0.125f;

            m_heightmap[z * g + x] = h * scale;
        }
    }
}

bool TerrainRenderer::CreateBuffers() {
    const uint32_t g = m_gridSize;
    const float step = m_spacing;

    float minH = m_heightmap[0], maxH = m_heightmap[0];
    for (uint32_t i = 0; i < m_vertexCount; ++i) {
        minH = std::min(minH, m_heightmap[i]);
        maxH = std::max(maxH, m_heightmap[i]);
    }
    float invRange = 1.0f / (maxH - minH + 0.001f);

    TerrainVertex *verts = new TerrainVertex[m_vertexCount];

    for (uint32_t z = 0; z < g; ++z) {
        for (uint32_t x = 0; x < g; ++x) {
            uint32_t idx = z * g + x;
            float h = m_heightmap[idx];

            // Engine uses Z-up coordinate system
            verts[idx].px = static_cast<float>(x) * step;
            verts[idx].py = static_cast<float>(z) * step;
            verts[idx].pz = h;

            float hL = (x > 0)     ? m_heightmap[z * g + (x - 1)] : h;
            float hR = (x < g - 1) ? m_heightmap[z * g + (x + 1)] : h;
            float hD = (z > 0)     ? m_heightmap[(z - 1) * g + x] : h;
            float hU = (z < g - 1) ? m_heightmap[(z + 1) * g + x] : h;

            float nx = -(hR - hL) / (2.0f * step);
            float ny = -(hU - hD) / (2.0f * step);
            float nz = 1.0f;
            float len = sqrtf(nx * nx + ny * ny + nz * nz);
            float invLen = 1.0f / (len + 0.00001f);
            verts[idx].nx = nx * invLen;
            verts[idx].ny = ny * invLen;
            verts[idx].nz = nz * invLen;

            float t = (h - minH) * invRange;
            uint8_t r, gv, b;
            if (t < 0.5f) {
                float t2 = t * 2.0f;
                r = static_cast<uint8_t>(t2 * 120.0f);
                gv = static_cast<uint8_t>((1.0f - t2 * 0.3f) * 180.0f);
                b = static_cast<uint8_t>((1.0f - t2) * 60.0f);
            } else {
                float t2 = (t - 0.5f) * 2.0f;
                r = static_cast<uint8_t>(120.0f + t2 * 135.0f);
                gv = static_cast<uint8_t>(126.0f + t2 * 129.0f);
                b = static_cast<uint8_t>(t2 * 200.0f);
            }
            verts[idx].r = r;
            verts[idx].g = gv;
            verts[idx].b = b;
            verts[idx].a = 255;
        }
    }

    uint32_t triCount = (g - 1) * (g - 1) * 2;
    m_indexCount = triCount * 3;
    uint16_t *indices = new uint16_t[m_indexCount];
    uint32_t i = 0;
    for (uint32_t z = 0; z < g - 1; ++z) {
        for (uint32_t x = 0; x < g - 1; ++x) {
            uint32_t i0 = z * g + x;
            uint32_t i1 = z * g + (x + 1);
            uint32_t i2 = (z + 1) * g + x;
            uint32_t i3 = (z + 1) * g + (x + 1);
            indices[i++] = static_cast<uint16_t>(i0);
            indices[i++] = static_cast<uint16_t>(i1);
            indices[i++] = static_cast<uint16_t>(i2);
            indices[i++] = static_cast<uint16_t>(i1);
            indices[i++] = static_cast<uint16_t>(i3);
            indices[i++] = static_cast<uint16_t>(i2);
        }
    }

    m_vbo = GLBuffer::Create(
        GL_ARRAY_BUFFER,
        m_vertexCount * sizeof(TerrainVertex),
        verts,
        GL_STATIC_DRAW,
        0
    );

    m_ibo = GLBuffer::Create(
        GL_ELEMENT_ARRAY_BUFFER,
        m_indexCount * sizeof(uint16_t),
        indices,
        GL_STATIC_DRAW,
        GL_UNSIGNED_SHORT
    );

    delete[] verts;
    delete[] indices;

    if (!m_vbo || !m_ibo) {
        Destroy();
        return false;
    }

    m_vertexFormat.m_Size = 3;
    m_vertexFormat.m_Attribs[0] = {0, 0, GLVT_FLOAT3, 0};
    m_vertexFormat.m_Attribs[1] = {0, 3, GLVT_FLOAT3, offsetof(TerrainVertex, nx)};
    m_vertexFormat.m_Attribs[2] = {0, 4, GLVT_UBYTE4N, offsetof(TerrainVertex, r)};

    // Create VAO and set up vertex attributes (core profile)
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo->m_BufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo->m_BufferID);

    // position: location=0, 3 floats
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
    glEnableVertexAttribArray(0);
    // normal: location=1, 3 floats
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, nx));
    glEnableVertexAttribArray(1);
    // color: location=2, 4 unsigned bytes, normalized
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, r));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    if (!CompileShaders()) {
        Destroy();
        return false;
    }

    return true;
}

bool TerrainRenderer::CompileShaders() {
    const char *vsSrc = R"(#version 330
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aNormal;
        layout(location = 2) in vec4 aColor;
        uniform mat4 uMVP;
        out vec3 vNormal;
        out vec4 vColor;
        void main() {
            gl_Position = uMVP * vec4(aPos, 1.0);
            vNormal = aNormal;
            vColor = aColor;
        })";

    const char *fsSrc = R"(#version 330
        in vec3 vNormal;
        in vec4 vColor;
        out vec4 fragColor;
        void main() {
            // Simple directional light from above
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
    if (!ok) { char buf[512]; glGetShaderInfoLog(vs, 512, nullptr, buf); fprintf(stderr, "Terrain VS error: %s\n", buf); }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
    if (!ok) { char buf[512]; glGetShaderInfoLog(fs, 512, nullptr, buf); fprintf(stderr, "Terrain FS error: %s\n", buf); }

    m_glslProgram = glCreateProgram();
    glAttachShader(m_glslProgram, vs);
    glAttachShader(m_glslProgram, fs);
    glLinkProgram(m_glslProgram);

    glGetProgramiv(m_glslProgram, GL_LINK_STATUS, &ok);
    if (!ok) { char buf[512]; glGetProgramInfoLog(m_glslProgram, 512, nullptr, buf); fprintf(stderr, "Terrain link error: %s\n", buf); }

    glDeleteShader(vs);
    glDeleteShader(fs);

    m_uniformMVP = glGetUniformLocation(m_glslProgram, "uMVP");

    return ok != 0;
}

void TerrainRenderer::Render() {
    if (!IsValid() || !m_glslProgram) return;

    GLDevice *device = GLDevice::Get();
    if (!device) return;

    // Get the view and projection matrices from the device
    float proj[16], view[16], world[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

    memcpy(proj, device->m_States.fixedFunc.transforms.projection.m, sizeof(proj));
    memcpy(view, device->m_States.fixedFunc.transforms.view.m, sizeof(view));

    // Y-flip projection for OpenGL (same as ApplyTransforms does)
    proj[4] *= -1.0f; proj[5] *= -1.0f; proj[6] *= -1.0f; proj[7] *= -1.0f;

    // Compute MVP = projection * view * world
    // C44Matrix is column-major: m[row + col*4] interpretation
    auto mulMat4 = [](const float *a, const float *b, float *dst) {
        for (int col = 0; col < 4; col++)
            for (int row = 0; row < 4; row++)
                dst[col*4 + row] = a[row]*b[col*4] + a[4+row]*b[col*4+1] + a[8+row]*b[col*4+2] + a[12+row]*b[col*4+3];
    };

    float viewWorld[16];
    mulMat4(view, world, viewWorld);
    float mvp[16];
    mulMat4(proj, viewWorld, mvp);

    // Set GL state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glDisable(GL_CULL_FACE);  // avoid culling issues from CW/CCW mismatch

    glUseProgram(m_glslProgram);
    glUniformMatrix4fv(m_uniformMVP, 1, GL_FALSE, mvp);

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

void TerrainRenderer::Destroy() {
    delete[] m_heightmap;
    m_heightmap = nullptr;

    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }

    if (m_glslProgram) {
        glDeleteProgram(m_glslProgram);
        m_glslProgram = 0;
    }

    if (m_vbo) {
        delete m_vbo;
        m_vbo = nullptr;
    }

    if (m_ibo) {
        delete m_ibo;
        m_ibo = nullptr;
    }

    m_vertexCount = 0;
    m_indexCount = 0;
}
