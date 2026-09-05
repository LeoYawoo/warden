#include "CWorld.h"
#include "Engine/Source/Gx/Gx.h"
#include "Engine/Source/Anim/Model2.h"
#include "Engine/Source/Gx/shader/CShaderEffect.h"
#include "Terrain/CTerrain.h"
#include <cmath>
#include <cstdlib>


uint32_t CWorld::s_enables;
uint32_t CWorld::s_enables2;
CTerrain *CWorld::s_terrain = nullptr;

void CWorld::Initialize() {
    CWorld::s_enables |=
            Enables::Enable_1
            | Enables::Enable_2
            | Enables::Enable_10
            | Enables::Enable_Culling
            | Enables::Enable_Shadow
            | Enables::Enable_100
            | Enables::Enable_200
            | Enables::Enable_800
            | Enables::Enable_4000
            | Enables::Enable_DetailDoodads
            | Enables::Enable_1000000
            | Enables::Enable_Particulates
            | Enables::Enable_LowDetail;

    // TODO

    if (GxCaps().m_shaderTargets[GxSh_Pixel] > GxShPS_none) {
        CWorld::s_enables |= Enables::Enable_PixelShader;
    }

    if (GxCaps().m_shaderTargets[GxSh_Vertex] > GxShVS_none) {
        CWorld::s_enables2 |= Enables2::Enable_VertexShader;
    }

    // TODO

    uint32_t m2Flags = M2GetCacheFlags();
    CShaderEffect::InitShaderSystem(
            (m2Flags & 0x8) != 0,
            (CWorld::s_enables2 & Enables2::Enable_HwPcf) != 0
    );

    if (!s_terrain) {
        s_terrain = static_cast<CTerrain*>(calloc(1, sizeof(CTerrain)));
        // Initialize a 64x64 cell terrain grid at origin (0, 0)
        // Each cell is 128 world units (matching War3 CELL_SIZE)
        s_terrain->Initialize(64, 64, 0.0f, 0.0f);

        // Generate procedural heightmap for testing
        uint32_t gx = s_terrain->GetCellsPerRow() + 1;
        uint32_t gy = s_terrain->GetCellsPerCol() + 1;
        uint32_t vertexCount = gx * gy;
        auto *heights = new float[vertexCount];

        for (uint32_t y = 0; y < gy; y++) {
            for (uint32_t x = 0; x < gx; x++) {
                float fx = static_cast<float>(x) / static_cast<float>(gx - 1);
                float fy = static_cast<float>(y) / static_cast<float>(gy - 1);
                float h = 0.0f;
                h += sinf(fx * 4.0f + 1.3f) * cosf(fy * 3.0f + 0.7f) * 30.0f;
                h += sinf(fx * 8.0f - fy * 5.0f + 2.1f) * 15.0f;
                h += cosf(fx * 12.0f + fy * 7.0f) * 8.0f;
                heights[y * gx + x] = h;
            }
        }
        s_terrain->SetHeights(heights);
        delete[] heights;
    }

    // TODO
}

void CWorld::Shutdown() {
    if (s_terrain) {
        delete s_terrain;
        s_terrain = nullptr;
    }
}
