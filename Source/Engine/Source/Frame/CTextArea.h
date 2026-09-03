#pragma once

#include "CControl.h"
#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CTextArea is a text area UI control

class CTextArea : public CControl {
public:
    CTextArea();
    virtual ~CTextArea();

    // TextArea properties
    const char* GetText() const;
    void SetText(const char* text);

    // TextArea operations
    void AppendText(const char* text);
    void ClearText();
    void InsertText(int32_t position, const char* text);

    // TextArea properties
    int32_t GetLineCount() const;
    int32_t GetCursorPosition() const;
    void SetCursorPosition(int32_t position);

    bool IsReadOnly() const;
    void SetReadOnly(bool readOnly);

protected:
    std::string m_text;
    int32_t m_cursorPosition;
    bool m_readOnly;
};
