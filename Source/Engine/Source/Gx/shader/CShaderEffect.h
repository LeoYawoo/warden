#pragma once

#include <cstdint>
#include "CGxShader.h"
#include "../Types.h"
#include "../../Tempest/C3Vector.h"
#include "../../Tempest/C4Vector.h"
#include "../../Tempest/CImVector.h"
#include "../../Tempest/C44Matrix.h"

using namespace Tempest;

// Forward declarations
struct CM2Lighting;

// Reverse engineered from Warcraft III binary
// CShaderEffect manages shader effects

class CShaderEffect {
public:
    // Static variables
    static int32_t s_usePcfFiltering;
    static int32_t s_enableShaders;

    // Member variables
    CGxShader *m_vertexShaders[64]; // TODO: Verify array size from IDA
    CGxShader *m_pixelShaders[64];  // TODO: Verify array size from IDA

    CShaderEffect() = default;
    ~CShaderEffect() = default;

    // Static member functions
    static void InitShaderSystem(bool hwSkinning, bool pcfFiltering);
    static void UpdateProjMatrix();
    static void SetShaders(uint32_t vertexPermute, uint32_t pixelPermute);
    static void SetLocalLighting(CM2Lighting *lighting, int32_t shaded, int32_t flags);
    static void SetFogEnabled(int32_t enabled);
    static void SetFogParams(float start, float end, float density, const CImVector &color);
    static void SetAlphaRef(float alphaRef);
    static void SetDiffuse(const C4Vector &diffuse);
    static void SetEmissive(const C4Vector &emissive);
    static void SetTexMtx_Identity(uint32_t index);
    static void SetTexMtx(const C44Matrix &matrix, uint32_t index);
    static void SetTexMtx_SphereMap(uint32_t index);

    // Instance member functions
    void SetCurrent();
    void InitEffect(const char *vsName, const char *psName);

    // TODO: Add member variables and functions based on IDA analysis
};
