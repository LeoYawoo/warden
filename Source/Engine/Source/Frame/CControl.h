#pragma once

#include "CSimpleFrame.h"
#include <cstdint>
#include <string>

// Forward declarations
class CControlSet;

// Reverse engineered from Warcraft III binary
// CControl is a base class for UI controls

class CControl : public CSimpleFrame {
public:
    CControl();
    virtual ~CControl();

    // Control properties
    const char* GetControlType() const;
    void SetControlType(const char* type);

    // Control state
    bool IsFocused() const;
    void SetFocused(bool focused);

    // Control operations
    virtual void OnClick();
    virtual void OnDoubleClick();
    virtual void OnMouseEnter();
    virtual void OnMouseLeave();
    virtual void OnKeyDown(int32_t key);
    virtual void OnKeyUp(int32_t key);

protected:
    std::string m_controlType;
    bool m_focused;
};
