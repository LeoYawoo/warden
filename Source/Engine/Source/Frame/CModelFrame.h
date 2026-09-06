#pragma once

#include "CSimpleFrame.h"
#include <cstdint>
#include <string>

// Forward declarations
class CM2Model;
class CMdlModel;

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

    // MDL model support
    bool IsMdlModel() const { return m_mdlModel != nullptr; }
    CMdlModel* GetMdlModel() const { return m_mdlModel; }

    // Update animation
    void Update(float deltaTime);

protected:
    std::string m_modelFile;
    bool m_playing;
    int32_t m_animation;
    float m_scale;

    // MDL model instance
    CMdlModel* m_mdlModel;

    // Internal methods
    bool LoadMdlModel(const char* filePath);
    void ReleaseMdlModel();
};
