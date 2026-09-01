#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainDeformation manages terrain deformation operations

class CTerrainDeformation {
public:
    // Deformation function info
    struct TDFunctionInfo {
        int32_t functionId;
        int32_t parameterCount;
        float* parameters;
    };

    CTerrainDeformation();
    ~CTerrainDeformation();

    // Deformation properties
    int32_t GetDeformationId() const;
    void SetDeformationId(int32_t id);

    // Deformation state
    bool IsActive() const;
    void SetActive(bool active);

    // Deformation functions
    void AddFunction(int32_t functionId, int32_t parameterCount, float* parameters);
    void RemoveFunction(int32_t functionId);
    size_t GetFunctionCount() const;

    // Apply deformation
    void Apply(CTerrain* terrain, float x, float y, float radius, float strength);

    // Undo deformation
    void Undo(CTerrain* terrain);

protected:
    int32_t m_deformationId;
    bool m_active;
    std::vector<TDFunctionInfo> m_functions;
    CTerrain* m_terrain;
};
