#pragma once

#include "CFrame.h"
#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CDialog is a dialog UI frame

class CDialog : public CFrame {
public:
    CDialog();
    virtual ~CDialog();

    // Dialog properties
    const char* GetTitle() const;
    void SetTitle(const char* title);

    // Dialog state
    bool IsModal() const;
    void SetModal(bool modal);

    // Dialog operations
    void Show();
    void Hide();
    void Close();

    // Dialog result
    int32_t GetResult() const;
    void SetResult(int32_t result);

protected:
    std::string m_title;
    bool m_modal;
    int32_t m_result;
};
