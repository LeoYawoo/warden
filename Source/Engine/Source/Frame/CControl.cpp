#include "CControl.h"

// Reverse engineered from Warcraft III binary

CControl::CControl() : m_focused(false) {}
CControl::~CControl() {}

const char* CControl::GetControlType() const { return m_controlType.c_str(); }
void CControl::SetControlType(const char* type) { m_controlType = type ? type : ""; }

bool CControl::IsFocused() const { return m_focused; }
void CControl::SetFocused(bool focused) { m_focused = focused; }

void CControl::OnClick() {}
void CControl::OnDoubleClick() {}
void CControl::OnMouseEnter() {}
void CControl::OnMouseLeave() {}
void CControl::OnKeyDown(int32_t key) { (void)key; }
void CControl::OnKeyUp(int32_t key) { (void)key; }
