#include "CThreadData.h"

// Reverse engineered from Warcraft III binary

namespace NIpse {

CThreadData::CThreadData() : m_threadId(0), m_valid(true), m_data(nullptr) {}

CThreadData::~CThreadData() {
    Shutdown();
}

int32_t CThreadData::GetThreadId() const { return m_threadId; }
void CThreadData::SetThreadId(int32_t id) { m_threadId = id; }

bool CThreadData::IsValid() const { return m_valid; }
void CThreadData::SetValid(bool valid) { m_valid = valid; }

void CThreadData::Initialize() {
    m_valid = true;
}

void CThreadData::Shutdown() {
    m_valid = false;
    m_data = nullptr;
}

} // namespace NIpse
