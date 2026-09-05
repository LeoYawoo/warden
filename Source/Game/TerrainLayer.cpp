#include "TerrainLayer.h"
#include "CWorld.h"
#include "Terrain/CTerrain.h"
#include "Engine/Source/Gx/Gx.h"
#include "Engine/Source/Gx/CCamera.h"

using namespace Tempest;

// Terrain rendering as a Screen layer callback
// This decouples Engine/Screen.cpp from Game/CWorld and Terrain/CTerrain

void TerrainLayerPaintFunc(void * /*param*/, const RECTF * /*rect*/, const RECTF * /*visible*/, float /*elapsedSec*/) {
    CTerrain *terrain = CWorld::GetTerrain();
    if (!terrain || !terrain->IsValid()) {
        return;
    }

    CRect windowSize;
    GxCapsWindowSize(windowSize);
    float w = windowSize.maxX - windowSize.minX;
    float h = windowSize.maxY - windowSize.minY;
    if (w <= 0 || h <= 0) {
        return;
    }

    CRect projRect = {0.0f, 0.0f, w, h};

    // Set up camera looking at terrain center
    CCamera camera;
    float cx = terrain->GetOriginX() + terrain->GetCellsPerRow() * terrain->GetCellSize() * 0.5f;
    float cy = terrain->GetOriginY() + terrain->GetCellsPerCol() * terrain->GetCellSize() * 0.5f;
    camera.m_position.Set(C3Vector(cx, cy - 200.0f, 300.0f));
    camera.m_target.Set(C3Vector(cx, cy, 0.0f));
    camera.m_distance.Set(1.0f);
    camera.m_fov.Set(1.2f);
    camera.m_zFar.Set(10000.0f);
    camera.m_zNear.Set(10.0f);
    camera.SetupWorldProjection(projRect, 0);

    // Render terrain
    terrain->Render();
}
