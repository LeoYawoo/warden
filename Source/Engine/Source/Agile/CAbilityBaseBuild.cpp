#include "CAbilityBaseBuild.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7883A3

CAbilityBaseBuild::CAbilityBaseBuild()
    : CAbilityInterfaced(),
      m_buildProgress(0.0f),
      m_buildTime(0.0f),
      m_resourceCost(),
      m_buildFlags(0),
      m_buildResult(0) {
    // Virtual table set in constructor
}

CAbilityBaseBuild::~CAbilityBaseBuild() {
    // Virtual destructor
}

void CAbilityBaseBuild::Bind(CAgentBaseAbs* agent) {
    // Bind ability to agent
    (void)agent;
}

void CAbilityBaseBuild::BindMini(CAgentBaseAbs* agent) {
    // Bind mini ability to agent
    (void)agent;
}

void CAbilityBaseBuild::Load(CDataStore& data) {
    // Load ability data
    (void)data;
}

void CAbilityBaseBuild::Save(CDataStore& data) {
    // Save ability data
    (void)data;
}

void CAbilityBaseBuild::LoadMini(CDataStore& data) {
    // Load mini ability data
    (void)data;
}

void CAbilityBaseBuild::SaveMini(CDataStore& data) {
    // Save mini ability data
    (void)data;
}

void CAbilityBaseBuild::Checklog(HSLOG* log) {
    // Check log for errors
    (void)log;
}

bool CAbilityBaseBuild::IsValidId(size_t id) {
    // Validate ability ID
    (void)id;
    return true;
}

float CAbilityBaseBuild::GetBuildProgress() const {
    return m_buildProgress;
}

void CAbilityBaseBuild::SetBuildProgress(float progress) {
    m_buildProgress = progress;
}

float CAbilityBaseBuild::GetBuildTime() const {
    return m_buildTime;
}

void CAbilityBaseBuild::SetBuildTime(float time) {
    m_buildTime = time;
}
