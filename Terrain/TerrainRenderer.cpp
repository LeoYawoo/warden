#include "TerrainRenderer.h"
#include "Graphic/gll/GLDevice.h"
#include "Graphic/gll/GLVertexArray.h"
#include "Graphic/Device.h"
#include "Graphic/Types.h"
#include <cmath>
#include <algorithm>
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

            verts[idx].px = static_cast<float>(x) * step;
            verts[idx].py = h;
            verts[idx].pz = static_cast<float>(z) * step;

            float hL = (x > 0)     ? m_heightmap[z * g + (x - 1)] : h;
            float hR = (x < g - 1) ? m_heightmap[z * g + (x + 1)] : h;
            float hD = (z > 0)     ? m_heightmap[(z - 1) * g + x] : h;
            float hU = (z < g - 1) ? m_heightmap[(z + 1) * g + x] : h;

            float nx = -(hR - hL) / (2.0f * step);
            float nz = -(hU - hD) / (2.0f * step);
            float ny = 1.0f;
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

    return true;
}

void TerrainRenderer::Render() {
    if (!IsValid()) { LOG("[Terrain] Render: not valid, skipping"); return; }

    GLDevice *device = GLDevice::Get();
    if (!device) { LOG("[Terrain] Render: no device, skipping"); return; }

    LOG("[Terrain] Render: saving state, setting FFP...");

    bool savedDepthTest    = device->m_States.depth.testEnable;
    bool savedDepthWrite   = device->m_States.depth.writeMask;
    int32_t savedDepthFunc = device->m_States.depth.compareFunc;
    bool savedLighting     = device->m_States.fixedFunc.lighting.enable;
    int32_t savedCullMode  = device->m_States.rasterizer.cullMode;

    device->SetDepthTestEnable(true);
    device->SetDepthWriteMask(true);
    device->SetDepthTestFunc(GL_LEQUAL);
    device->SetLightingEnable(true);
    device->SetCullMode(GL_CCW);

    device->SetShader(GLShader::eVertexShader, nullptr);
    device->SetShader(GLShader::ePixelShader, nullptr);

    float worldIdentity[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    device->SetTransform(0x57524C44 /*'WRLD'*/, worldIdentity);

    device->SetVertexBuffer(0, m_vbo, 0, sizeof(TerrainVertex));
    device->SetVertexFormat(&m_vertexFormat);
    device->SetIndexBuffer(m_ibo);

    LOG("[Terrain] GLLDraw: vertices=%u indices=%u", m_vertexCount, m_indexCount);
    device->GLLDraw(GL_TRIANGLES, 0, m_vertexCount - 1, 0, 0, m_indexCount);
    LOG("[Terrain] GLLDraw done");

    device->SetDepthTestEnable(savedDepthTest);
    device->SetDepthWriteMask(savedDepthWrite);
    device->SetDepthTestFunc(savedDepthFunc);
    device->SetLightingEnable(savedLighting);
    device->SetCullMode(savedCullMode);

    LOG("[Terrain] State restored, marking dirty");

    if (g_theGxDevicePtr) {
        g_theGxDevicePtr->IRsDirty(GxRs_DepthTest);
        g_theGxDevicePtr->IRsDirty(GxRs_DepthFunc);
        g_theGxDevicePtr->IRsDirty(GxRs_DepthWrite);
        g_theGxDevicePtr->IRsDirty(GxRs_Lighting);
        g_theGxDevicePtr->IRsDirty(GxRs_Culling);
        g_theGxDevicePtr->IRsDirty(GxRs_VertexShader);
        g_theGxDevicePtr->IRsDirty(GxRs_PixelShader);
    }
}

void TerrainRenderer::Destroy() {
    delete[] m_heightmap;
    m_heightmap = nullptr;

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
