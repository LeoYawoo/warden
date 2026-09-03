#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CTitle manages the title screen

class CTitle {
public:
    CTitle();
    ~CTitle();

    // Title operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Title properties
    const char* GetTitle() const;
    void SetTitle(const char* title);

    const char* GetSubtitle() const;
    void SetSubtitle(const char* subtitle);

    // Title state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    bool m_initialized;
    bool m_visible;
    std::string m_title;
    std::string m_subtitle;
};
