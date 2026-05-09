#include "CWorld.h"
#include "Graphic/Gx.h"
#include "Anim/Model2.h"
#include "Graphic/shader/CShaderEffect.h"
#include "Terrain/TerrainRenderer.h"
#include "Graphic/CCamera.h"
#include "Graphic/Screen.h"


uint32_t CWorld::s_enables;
uint32_t CWorld::s_enables2;
TerrainRenderer *CWorld::s_terrain = nullptr;
static HOBJECT s_terrainLayer = nullptr;

static void TerrainLayerPaint(void *param, const RECTF *rect, const RECTF *visible, float elapsedSec) {
    TerrainRenderer *terrain = static_cast<TerrainRenderer *>(param);
    if (!terrain || !terrain->IsValid()) return;

    CRect windowSize;
    GxCapsWindowSize(windowSize);
    float width = windowSize.maxX - windowSize.minX;
    float height = windowSize.maxY - windowSize.minY;
    if (width <= 0 || height <= 0) return;

    CRect projRect = {0.0f, 0.0f, width, height};

    CCamera camera;
    camera.m_position.Set(C3Vector(150.0f, 120.0f, 150.0f));
    camera.m_target.Set(C3Vector(128.0f, 0.0f, 128.0f));
    camera.m_distance.Set(1.0f);
    camera.m_fov.Set(0.8f);
    camera.m_zFar.Set(2000.0f);
    camera.m_zNear.Set(1.0f);
    camera.SetupWorldProjection(projRect, 0);

    terrain->Render();
}

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
        s_terrain = new TerrainRenderer();
        s_terrain->Initialize(33, 8.0f, 50.0f);
    }

    RECTF terrainRect = {0.0f, 0.0f, 1.0f, 1.0f};
    ScrnLayerCreate(&terrainRect, 0.0f, 0x4, s_terrain, &TerrainLayerPaint, &s_terrainLayer);

    // TODO
}

void CWorld::Shutdown() {
    if (s_terrain) {
        s_terrain->Destroy();
        delete s_terrain;
        s_terrain = nullptr;
    }
}
