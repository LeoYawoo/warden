#include "CShaderEffect.h"

// TODO: Reverse engineer from IDA

// Static member variable definitions
int32_t CShaderEffect::s_usePcfFiltering = 0;
int32_t CShaderEffect::s_enableShaders = 0;

void CShaderEffect::InitShaderSystem(bool /*hwSkinning*/, bool /*pcfFiltering*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::UpdateProjMatrix() {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetShaders(uint32_t /*vertexPermute*/, uint32_t /*pixelPermute*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetLocalLighting(CM2Lighting * /*lighting*/, int32_t /*shaded*/, int32_t /*flags*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetFogEnabled(int32_t /*enabled*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetFogParams(float /*start*/, float /*end*/, float /*density*/, const CImVector & /*color*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetAlphaRef(float /*alphaRef*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetDiffuse(const C4Vector & /*diffuse*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetEmissive(const C4Vector & /*emissive*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetTexMtx_Identity(uint32_t /*index*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetTexMtx(const C44Matrix & /*matrix*/, uint32_t /*index*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetTexMtx_SphereMap(uint32_t /*index*/) {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::SetCurrent() {
    // TODO: Reverse engineer from IDA
}

void CShaderEffect::InitEffect(const char * /*vsName*/, const char * /*psName*/) {
    // TODO: Reverse engineer from IDA
}
