#include "CTextArea.h"

// Reverse engineered from Warcraft III binary

CTextArea::CTextArea() : m_cursorPosition(0), m_readOnly(false) { m_controlType = "TextArea"; }
CTextArea::~CTextArea() {}

const char* CTextArea::GetText() const { return m_text.c_str(); }
void CTextArea::SetText(const char* text) { m_text = text ? text : ""; m_cursorPosition = 0; }

void CTextArea::AppendText(const char* text) {
    if (text && !m_readOnly) m_text += text;
}

void CTextArea::ClearText() {
    m_text.clear();
    m_cursorPosition = 0;
}

void CTextArea::InsertText(int32_t position, const char* text) {
    if (text && !m_readOnly && position >= 0 && static_cast<size_t>(position) <= m_text.size()) {
        m_text.insert(position, text);
    }
}

int32_t CTextArea::GetLineCount() const {
    int32_t count = 1;
    for (char c : m_text) {
        if (c == '\n') count++;
    }
    return count;
}

int32_t CTextArea::GetCursorPosition() const { return m_cursorPosition; }
void CTextArea::SetCursorPosition(int32_t position) { m_cursorPosition = std::max(0, std::min(position, static_cast<int32_t>(m_text.size()))); }

bool CTextArea::IsReadOnly() const { return m_readOnly; }
void CTextArea::SetReadOnly(bool readOnly) { m_readOnly = readOnly; }
