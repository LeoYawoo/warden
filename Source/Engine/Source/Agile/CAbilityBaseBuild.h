#pragma once

#include "CAbilityInterfaced.h"
#include "Float.h"

// Forward declarations
class HSLOG;

// Reverse engineered from Warcraft III binary
// Address: 0x7883A3
// CAbilityBaseBuild is the base build ability

class CAbilityBaseBuild : public CAbilityInterfaced {
public:
    CAbilityBaseBuild();
    virtual ~CAbilityBaseBuild();

    // Build operations
    virtual void Bind(CAgentBaseAbs* agent);
    virtual void BindMini(CAgentBaseAbs* agent);

    virtual void Load(CDataStore& data);
    virtual void Save(CDataStore& data);

    virtual void LoadMini(CDataStore& data);
    virtual void SaveMini(CDataStore& data);

    virtual void Checklog(HSLOG* log);

    static bool IsValidId(size_t id);

    // Get build progress
    float GetBuildProgress() const;

    // Set build progress
    void SetBuildProgress(float progress);

    // Get build time
    float GetBuildTime() const;

    // Set build time
    void SetBuildTime(float time);

protected:
    float m_buildProgress;  // offset +108
    float m_buildTime;      // offset +116
    Float m_resourceCost;   // offset +124
    int m_buildFlags;       // offset +140
    int m_buildResult;      // offset +144
};
