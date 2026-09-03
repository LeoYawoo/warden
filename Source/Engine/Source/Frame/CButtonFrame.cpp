#include "CButtonFrame.h"

// Reverse engineered from Warcraft III binary

CButtonFrame::CButtonFrame() : m_pressed(false) { m_controlType = "Button"; }
CButtonFrame::~CButtonFrame() {}

const char* CButtonFrame::GetButtonText() const { return m_buttonText.c_str(); }
void CButtonFrame::SetButtonText(const char* text) { m_buttonText = text ? text : ""; }

bool CButtonFrame::IsPressed() const { return m_pressed; }
void CButtonFrame::SetPressed(bool pressed) { m_pressed = pressed; }

void CButtonFrame::OnClick() {
    m_pressed = !m_pressed;
}

void CButtonFrame::OnDoubleClick() {
    m_pressed = true;
}
