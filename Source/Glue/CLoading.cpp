#include "CLoading.h"

// Reverse engineered from Warcraft III binary

CLoading::CLoading() : m_initialized(false), m_loading(false), m_progress(0.0f) {}
CLoading::~CLoading() { Shutdown(); }

bool CLoading::Initialize() {
    m_initialized = true;
    m_loading = false;
    m_progress = 0.0f;
    return true;
}

void CLoading::Shutdown() {
    m_initialized = false;
    m_loading = false;
}

bool CLoading::IsInitialized() const { return m_initialized; }

float CLoading::GetProgress() const { return m_progress; }
void CLoading::SetProgress(float progress) { m_progress = progress; }

const char* CLoading::GetStatusMessage() const { return m_statusMessage.c_str(); }
void CLoading::SetStatusMessage(const char* message) { m_statusMessage = message ? message : ""; }

bool CLoading::IsLoading() const { return m_loading; }
void CLoading::SetLoading(bool loading) { m_loading = loading; }
