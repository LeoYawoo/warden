#include "COptionsMenu.h"

// Reverse engineered from Warcraft III binary

COptionsMenu::COptionsMenu()
    : m_initialized(false), m_visible(false), m_volume(50),
      m_fullscreen(false), m_screenWidth(800), m_screenHeight(600) {
}

COptionsMenu::~COptionsMenu() { Shutdown(); }

bool COptionsMenu::Initialize() {
    m_initialized = true;
    return true;
}

void COptionsMenu::Shutdown() {
    m_initialized = false;
}

bool COptionsMenu::IsInitialized() const { return m_initialized; }

int32_t COptionsMenu::GetVolume() const { return m_volume; }
void COptionsMenu::SetVolume(int32_t volume) { m_volume = volume; }

bool COptionsMenu::IsFullscreen() const { return m_fullscreen; }
void COptionsMenu::SetFullscreen(bool fullscreen) { m_fullscreen = fullscreen; }

int32_t COptionsMenu::GetScreenWidth() const { return m_screenWidth; }
int32_t COptionsMenu::GetScreenHeight() const { return m_screenHeight; }

void COptionsMenu::SetScreenResolution(int32_t width, int32_t height) {
    m_screenWidth = width;
    m_screenHeight = height;
}

bool COptionsMenu::IsVisible() const { return m_visible; }
void COptionsMenu::SetVisible(bool visible) { m_visible = visible; }
