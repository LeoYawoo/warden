#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// COptionsMenu manages the options menu

class COptionsMenu {
public:
    COptionsMenu();
    ~COptionsMenu();

    // Menu operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Options
    int32_t GetVolume() const;
    void SetVolume(int32_t volume);

    bool IsFullscreen() const;
    void SetFullscreen(bool fullscreen);

    int32_t GetScreenWidth() const;
    int32_t GetScreenHeight() const;
    void SetScreenResolution(int32_t width, int32_t height);

    // Menu state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    bool m_initialized;
    bool m_visible;
    int32_t m_volume;
    bool m_fullscreen;
    int32_t m_screenWidth;
    int32_t m_screenHeight;
};
