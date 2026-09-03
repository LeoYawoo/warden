#include "CEditBox.h"

// Reverse engineered from Warcraft III binary

CEditBox::CEditBox() : m_maxLength(256), m_password(false) { m_controlType = "EditBox"; }
CEditBox::~CEditBox() {}

const char* CEditBox::GetText() const { return m_text.c_str(); }
void CEditBox::SetText(const char* text) { m_text = text ? text : ""; }

const char* CEditBox::GetPlaceholder() const { return m_placeholder.c_str(); }
void CEditBox::SetPlaceholder(const char* placeholder) { m_placeholder = placeholder ? placeholder : ""; }

int32_t CEditBox::GetMaxLength() const { return m_maxLength; }
void CEditBox::SetMaxLength(int32_t maxLength) { m_maxLength = maxLength; }

bool CEditBox::IsPassword() const { return m_password; }
void CEditBox::SetPassword(bool password) { m_password = password; }

void CEditBox::OnClick() {
    SetFocused(true);
}

void CEditBox::OnKeyDown(int32_t key) {
    if (key == 8 && !m_text.empty()) {
        m_text.pop_back();
    }
}
