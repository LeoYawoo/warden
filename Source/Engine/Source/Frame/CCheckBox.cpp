#include "CCheckBox.h"

// Reverse engineered from Warcraft III binary

CCheckBox::CCheckBox() : m_checked(false) { m_controlType = "CheckBox"; }
CCheckBox::~CCheckBox() {}

bool CCheckBox::IsChecked() const { return m_checked; }
void CCheckBox::SetChecked(bool checked) { m_checked = checked; }

const char* CCheckBox::GetText() const { return m_text.c_str(); }
void CCheckBox::SetText(const char* text) { m_text = text ? text : ""; }

void CCheckBox::OnClick() {
    m_checked = !m_checked;
}
