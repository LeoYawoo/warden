#include "CRlAgent.h"

// Reverse engineered from Warcraft III binary

namespace NIpse {

CRlAgent::CRlAgent() : m_agentId(0), m_initialized(false), m_running(false) {}

CRlAgent::~CRlAgent() {}

int32_t CRlAgent::GetAgentId() const { return m_agentId; }
void CRlAgent::SetAgentId(int32_t id) { m_agentId = id; }

const char* CRlAgent::GetAgentName() const { return m_agentName.c_str(); }
void CRlAgent::SetAgentName(const char* name) { m_agentName = name ? name : ""; }

bool CRlAgent::IsInitialized() const { return m_initialized; }
void CRlAgent::SetInitialized(bool initialized) { m_initialized = initialized; }

bool CRlAgent::IsRunning() const { return m_running; }
void CRlAgent::SetRunning(bool running) { m_running = running; }

void CRlAgent::Initialize() {
    m_initialized = true;
}

void CRlAgent::Shutdown() {
    m_running = false;
    m_initialized = false;
}

void CRlAgent::Update(float deltaTime) {
    (void)deltaTime;
    // TODO: Implement update logic
}

void CRlAgent::Save(CDataStore& data) {
    (void)data;
    // TODO: Implement save logic
}

void CRlAgent::Load(CDataStore& data) {
    (void)data;
    // TODO: Implement load logic
}

} // namespace NIpse
