#pragma once

#include <cstdint>

// Forward declarations
class CShaderEffect;

// Reverse engineered from Warcraft III binary
// CShaderEffectManager manages shader effects

class CShaderEffectManager {
public:
    CShaderEffectManager() = default;
    ~CShaderEffectManager() = default;

    // Static member functions
    static CShaderEffect *GetEffect(const char *effectName);
    static CShaderEffect *CreateEffect(const char *effectName);

    // TODO: Add member variables and functions based on IDA analysis
};
