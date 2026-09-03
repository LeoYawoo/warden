#pragma once

#include "CSimpleFrame.h"
#include <cstdint>
#include <string>

// Forward declarations
class CM2Model;

// Reverse engineered from Warcraft III binary
// CModelFrame displays 3D models

class CModelFrame : public CSimpleFrame {
public:
    CModelFrame();
    virtual ~CModelFrame();

    // Model properties
    const char* GetModelFile() const;
    void SetModelFile(const char* file);

    // Model state
    bool IsPlaying() const;
    void SetPlaying(bool playing);

    // Model animation
    void SetAnimation(int32_t animId);
    int32_t GetAnimation() const;

    // Model scale
    float GetScale() const;
    void SetScale(float scale);

protected:
    std::string m_modelFile;
    bool m_playing;
    int32_t m_animation;
    float m_scale;
};
