#include "CCaptainAI.h"

// Reverse engineered from Warcraft III binary

CCaptainAI::CCaptainAI() : m_captainId(0), m_enabled(true) {}
CCaptainAI::~CCaptainAI() {}

int32_t CCaptainAI::GetCaptainId() const { return m_captainId; }
void CCaptainAI::SetCaptainId(int32_t id) { m_captainId = id; }

bool CCaptainAI::IsEnabled() const { return m_enabled; }
void CCaptainAI::SetEnabled(bool enabled) { m_enabled = enabled; }

void CCaptainAI::Update(float deltaTime) {
    // Update AI logic
    (void)deltaTime;
}

void CCaptainAI::Reset() {
    m_captainId = 0;
    m_enabled = true;
}
