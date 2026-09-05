#pragma once

// TerrainLayer - Terrain rendering as a Screen layer callback
// Decouples Engine (Screen.cpp) from Game (CWorld/CTerrain)

#include <cstdint>

struct RECTF;

void TerrainLayerPaintFunc(void *param, const RECTF *rect, const RECTF *visible, float elapsedSec);
