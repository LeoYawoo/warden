#include "CSimpleFrame.h"

// Reverse engineered from Warcraft III binary

CSimpleFrame::CSimpleFrame()
    : m_frameLevel(0), m_mouseEnabled(true), m_keyboardEnabled(true) {
}

CSimpleFrame::~CSimpleFrame() {
}

int32_t CSimpleFrame::GetFrameLevel() const { return m_frameLevel; }
void CSimpleFrame::SetFrameLevel(int32_t level) { m_frameLevel = level; }

bool CSimpleFrame::IsMouseEnabled() const { return m_mouseEnabled; }
void CSimpleFrame::SetMouseEnabled(bool enabled) { m_mouseEnabled = enabled; }

bool CSimpleFrame::IsKeyboardEnabled() const { return m_keyboardEnabled; }
void CSimpleFrame::SetKeyboardEnabled(bool enabled) { m_keyboardEnabled = enabled; }

void CSimpleFrame::Update(float deltaTime) {
    CFrame::Update(deltaTime);
}

void CSimpleFrame::Render() {
    CFrame::Render();
}

bool CSimpleFrame::HandleInput(int32_t message, int32_t wParam, int32_t lParam) {
    if (!m_enabled || !m_mouseEnabled) return false;
    return CFrame::HandleInput(message, wParam, lParam);
}
