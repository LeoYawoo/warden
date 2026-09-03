#pragma once

#include "CControl.h"
#include <cstdint>
#include <string>

// Forward declarations
struct CEditBox;

// Reverse engineered from Warcraft III binary
// CEditBox is an edit box UI control

class CEditBox : public CControl {
public:
    CEditBox();
    virtual ~CEditBox();

    // EditBox properties
    const char* GetText() const;
    void SetText(const char* text);

    const char* GetPlaceholder() const;
    void SetPlaceholder(const char* placeholder);

    // EditBox state
    int32_t GetMaxLength() const;
    void SetMaxLength(int32_t maxLength);

    bool IsPassword() const;
    void SetPassword(bool password);

    // EditBox operations
    virtual void OnClick() override;
    virtual void OnKeyDown(int32_t key) override;

protected:
    std::string m_text;
    std::string m_placeholder;
    int32_t m_maxLength;
    bool m_password;
};
