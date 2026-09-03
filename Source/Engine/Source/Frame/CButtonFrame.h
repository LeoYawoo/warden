#pragma once

#include "CControl.h"
#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CButtonFrame is a button UI control

class CButtonFrame : public CControl {
public:
    CButtonFrame();
    virtual ~CButtonFrame();

    // Button properties
    const char* GetButtonText() const;
    void SetButtonText(const char* text);

    // Button state
    bool IsPressed() const;
    void SetPressed(bool pressed);

    // Button operations
    virtual void OnClick() override;
    virtual void OnDoubleClick() override;

protected:
    std::string m_buttonText;
    bool m_pressed;
};
