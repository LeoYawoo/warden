#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CInfoBar displays information

class CInfoBar {
public:
    CInfoBar();
    ~CInfoBar();

    // Info bar properties
    const char* GetInfoText() const;
    void SetInfoText(const char* text);

    // Info bar state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    std::string m_infoText;
    bool m_visible;
};
