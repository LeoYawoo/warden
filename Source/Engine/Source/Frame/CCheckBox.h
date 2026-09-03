#pragma once

#include "CControl.h"
#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CCheckBox is a checkbox UI control

class CCheckBox : public CControl {
public:
    CCheckBox();
    virtual ~CCheckBox();

    // CheckBox properties
    bool IsChecked() const;
    void SetChecked(bool checked);

    // CheckBox text
    const char* GetText() const;
    void SetText(const char* text);

    // CheckBox operations
    virtual void OnClick() override;

protected:
    bool m_checked;
    std::string m_text;
};
