#pragma once

#include "CFrame.h"
#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CSimpleFrame is a simplified frame implementation

class CSimpleFrame : public CFrame {
public:
    CSimpleFrame();
    virtual ~CSimpleFrame();

    // SimpleFrame properties
    int32_t GetFrameLevel() const;
    void SetFrameLevel(int32_t level);

    // SimpleFrame state
    bool IsMouseEnabled() const;
    void SetMouseEnabled(bool enabled);

    bool IsKeyboardEnabled() const;
    void SetKeyboardEnabled(bool enabled);

    // SimpleFrame operations
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual bool HandleInput(int32_t message, int32_t wParam, int32_t lParam) override;

protected:
    int32_t m_frameLevel;
    bool m_mouseEnabled;
    bool m_keyboardEnabled;
};
