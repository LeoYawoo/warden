#include "CTerrainDeformation.h"
#include "CTerrain.h"
#include <algorithm>
#include <cmath>

// Reverse engineered from Warcraft III binary

CTerrainDeformation::CTerrainDeformation()
    : m_deformationId(0),
      m_active(false),
      m_terrain(nullptr) {
}

CTerrainDeformation::~CTerrainDeformation() {
}

int32_t CTerrainDeformation::GetDeformationId() const {
    return m_deformationId;
}

void CTerrainDeformation::SetDeformationId(int32_t id) {
    m_deformationId = id;
}

bool CTerrainDeformation::IsActive() const {
    return m_active;
}

void CTerrainDeformation::SetActive(bool active) {
    m_active = active;
}

void CTerrainDeformation::AddFunction(int32_t functionId, int32_t parameterCount, float* parameters) {
    TDFunctionInfo info;
    info.functionId = functionId;
    info.parameterCount = parameterCount;
    info.parameters = parameters;
    m_functions.push_back(info);
}

void CTerrainDeformation::RemoveFunction(int32_t functionId) {
    m_functions.erase(
        std::remove_if(m_functions.begin(), m_functions.end(),
            [functionId](const TDFunctionInfo& info) { return info.functionId == functionId; }),
        m_functions.end()
    );
}

size_t CTerrainDeformation::GetFunctionCount() const {
    return m_functions.size();
}

void CTerrainDeformation::Apply(CTerrain* terrain, float x, float y, float radius, float strength) {
    if (!terrain || !m_active) {
        return;
    }

    int32_t tileSize = terrain->GetTileSize();
    int32_t tileX = static_cast<int32_t>(x / tileSize);
    int32_t tileY = static_cast<int32_t>(y / tileSize);
    int32_t tileRadius = static_cast<int32_t>(radius / tileSize);

    for (int32_t dy = -tileRadius; dy <= tileRadius; dy++) {
        for (int32_t dx = -tileRadius; dx <= tileRadius; dx++) {
            int32_t tx = tileX + dx;
            int32_t ty = tileY + dy;

            if (terrain->InBoundsInt(tx, ty)) {
                float dist = std::sqrt(static_cast<float>(dx * dx + dy * dy)) * tileSize;
                if (dist <= radius) {
                    float factor = 1.0f - (dist / radius);
                    float currentHeight = terrain->GetHeight(tx, ty);
                    terrain->SetHeight(tx, ty, currentHeight + strength * factor);
                }
            }
        }
    }
}

void CTerrainDeformation::Undo(CTerrain* terrain) {
    (void)terrain;
    // Undo implementation would require storing original heights
}
